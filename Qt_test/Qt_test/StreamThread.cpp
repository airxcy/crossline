#include "StreamThread.h"

template<typename T>
T max1D(vector<T>& vec)
{
	T maxval=vec[0];
	for(int i=0;i<vec.size();i++)
	{
		if(vec[i]>maxval)
			maxval=vec[i];
	}
	return maxval;
}
template double max1D<double>(vector<double>&); 
template float max1D<float>(vector<float>&); 
template int max1D<int>(vector<int>&);

StreamThread::StreamThread(QObject *parent) : QThread(parent)
{
    restart = false;
    abort = false;
	hasGT=false;
	//AppObj=(Qt_test*)parent;
	pointA[0]=0,pointA[1]=0,pointB[0]=0,pointB[1]=0;
	line_x=vector<int>();
	line_y=vector<int>();
}
StreamThread::~StreamThread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}
StreamThread & StreamThread :: operator= (  const StreamThread & oriStreamthread )
{
	//newStreamthread.
	//newStreamthread =StreamThread(QObject *parent) 
	StreamThread one = new StreamThread();
	return one;
}
bool StreamThread::checkPoints()
{
	return ((pointA[0]==pointB[0])&&(pointA[1]==pointB[1])) || pointA[0]<0 || pointA[0]>=vid_width
		||pointB[0]<0 || pointB[0]>=vid_width
		||pointB[1]<0 || pointB[1]>=vid_height
		||pointA[1]<0 || pointA[1]>=vid_height;
}
void StreamThread::streaming()
{
	forever
	{
		if (init())
		{
			emit initUI();
			a_frame=Mat::zeros(vid_height,vid_width,IMGTYPE);
			c_frame=Mat::zeros(vid_height,vid_width,CV_8UC3);
			bg_cframe=Mat::zeros(vid_height,vid_width,CV_8UC3);
			bg_frame=Mat::zeros(vid_height,vid_width,IMGTYPE);
			plot1_frame=Mat::zeros(plot1_height,plot1_width,CV_8UC3);
			plot1_frameL=Mat::zeros(plot1_height*2,plot1_width*2,CV_8UC3);
			int frameidx=0;
			while(vid_stream.readFrame(c_frame))
			{
				if (restart)
						break;
				if (abort)
						return;
				if(c_frame.channels()==3)
				{
					cvtColor(c_frame, a_frame, CV_BGR2GRAY);
					cvtColor(c_frame, c_frame, CV_BGR2RGB);
				}
				else
				{
					a_frame=c_frame.clone();
					cvtColor(c_frame, c_frame, CV_GRAY2RGB);
				}
				
				bg_stream.getBgMask(c_frame,bg_frame);
				cvtColor(bg_frame, bg_cframe, CV_GRAY2RGB);
				//vid_stream.updateBuff(a_frame.data);
				vid_slice.fromAFrame(a_frame.data);
				bg_slice.fromAFrame(bg_frame.data);
				features.updateFeat(bg_slice.data_buff);
				if(hasGT)
				{
					gt_label.loadXYIdx(frameidx);
					features.updateFeatCount(gt_label.curCrossSum);
					regresion.updateIDLinear(features);
				}
				regresion.IDLinear(features);
				
				drawItems();
				
				usingFrames=true;
				emit aFrameDone();
				cleanUpFrames();
				frameidx++;
			}
		}
		else
		{
			emit debug( "init Failed");
		}
		mutex.lock();
        if (!restart)
            condition.wait(&mutex);
        restart = false;
        mutex.unlock();
	}
}
void StreamThread::cleanUpFrames()
{
	while(usingFrames){}
	memset(plot1_frame.data,0,plot1_frame.total()*plot1_frame.elemSize());
}
void StreamThread::plot1()
{
	Scalar colorArea=Scalar(0, 255, 0);
	Scalar colorCount=Scalar(255, 255, 0);
	Scalar colorText=Scalar(255, 255, 255);
	Scalar colorReg=Scalar(0, 255, 255);
	Scalar errColor=Scalar(255,200,255);
	for(int i=0;i<5;i++)
	{
		line(plot1_frame,Point(0,plot1_frame.size[0]*(1-i/5.0)), Point(5,plot1_frame.size[0]*(1-i/5.0)),colorCount);
		line(plot1_frame,Point(plot1_frame.size[1]-1,plot1_frame.size[0]*(1-i/5.0)), Point(plot1_frame.size[1]-6,plot1_frame.size[0]*(1-i/5.0)), colorArea);
		line(plot1_frame,Point(plot1_frame.size[1]/2-3,plot1_frame.size[0]*(1-i/5.0)), Point(plot1_frame.size[1]/2+3,plot1_frame.size[0]*(1-i/5.0)), colorReg);
	}
	/**GT count**/
	if(gt_label.hasGT)
	{
		int sumcountmax=max1D(gt_label.crossedSum);
		if(sumcountmax>=plot_count_max)plot_count_max=sumcountmax+1;
		for(int i=0;i<5;i++)
		{
			sprintf(strbuff,"%.1f\0",i*plot_count_max/5.0);
			cv::putText(plot1_frame, strbuff, Point(0,plot1_frame.size[0]*(1-i/5.0)), FONT_HERSHEY_SIMPLEX, 0.3,colorText );
		}
		int xlinepos=0;
		int i=gt_label.cross_head;
		do{
			float sumcount=gt_label.crossedSum[i];
			float inscount=gt_label.cross_N[i];
			int sumcounty=sumcount/plot_count_max*plot1_frame.size[0];
			int inscounty=inscount/plot_count_max*plot1_frame.size[0]*10;
			if(inscounty>0)
				//plot1_frame.at<cv::Vec3b>((plot1_frame.size[0]-1)-inscounty,xlinepos)=cv::Vec3b(255,0,0);
				line(plot1_frame,Point(xlinepos,plot1_frame.size[0]-1), Point(xlinepos,(plot1_frame.size[0]-1)-inscounty), Scalar(255, 0, 0));
			if(sumcounty>0)
				plot1_frame.at<cv::Vec3b>((plot1_frame.size[0]-1)-sumcounty,xlinepos)=cv::Vec3b(colorCount[0],colorCount[1],colorCount[2]);
			i=(i+1)%buff_N;
			xlinepos++;
		}while(i!=gt_label.cross_tail);
		//sprintf(strbuff,"%f",plot_count_max);
		//debug(strbuff);
	}
	/** area **/
	int areamax=max1D(features.areavect);
	if(areamax>=plot_area_max)plot_area_max=areamax+1;
	for(int i=0;i<5;i++)
	{
		sprintf(strbuff,"%.1fK\0",i*plot_area_max/5.0/1000);
		cv::putText(plot1_frame, strbuff, Point(plot1_frame.size[1]-40,plot1_frame.size[0]*(1-i/5.0)), FONT_HERSHEY_SIMPLEX, 0.3,colorText );
	}
	int xlinepos=0;
	int i=features.head;
	do{
		int areay=features.areavect[i]/plot_area_max*plot1_frame.size[0];
		if(areay>0)
			plot1_frame.at<cv::Vec3b>((plot1_frame.size[0]-1)-areay,xlinepos)=cv::Vec3b(colorArea[0],colorArea[1],colorArea[2]);
			//circle(plot1_frame, Point(xlinepos,(plot1_frame.size[0]-1)-areay), 2, colorArea, 2, 8, 0);
		i=(i+1)%buff_N;
		xlinepos++;
	}while(i!=features.tail);

	/**regression**/
	
	float fcount =max1D(regresion.countvec);
	if(fcount>=plot_reg_max)plot_reg_max=fcount+1;
	for(int i=0;i<5;i++)
	{
		sprintf(strbuff,"%.1fK\0",i*plot_reg_max/5.0);
		cv::putText(plot1_frame, strbuff, Point(plot1_frame.size[1]/2-40,plot1_frame.size[0]*(1-i/5.0)), FONT_HERSHEY_SIMPLEX, 0.3,colorText );
	}
	
	float errval=0;
	 xlinepos=0;
	// for(i=regresion.head;i!=regresion.tail;i=(i+1)%buff_N)
	 i=regresion.head;
	do{
		int regcount=regresion.countvec[i]/plot_reg_max*plot1_frame.size[0];
		//sprintf(strbuff,"%d,%f",regcount,regresion.countvec[i]);
		//debug(strbuff);
		if(regcount>0)
			plot1_frame.at<cv::Vec3b>((plot1_frame.size[0]-1)-regcount,xlinepos)=cv::Vec3b(colorReg[0],colorReg[1],colorReg[2]);
		errval = gt_label.crossedSum[i]-regresion.countvec[i];
		int errcount=errval/plot_reg_max*plot1_frame.size[0];
		if(errcount>0)
			plot1_frame.at<cv::Vec3b>((plot1_frame.size[0]-1)-errcount,xlinepos)=cv::Vec3b(errColor[0],errColor[1],errColor[2]);
		i=(i+1)%buff_N;
		xlinepos++;
	}while(i!=regresion.tail);
	sprintf(strbuff,"cnt:%d\0",gt_label.crossedSum[max(gt_label.cross_tail-1,0)]);
	cv::putText(plot1_frame, strbuff, Point(0,20), FONT_HERSHEY_SIMPLEX, 0.5, colorCount );
	sprintf(strbuff,"area:%.1fKpx\0",features.curArea/1000.0);
	cv::putText(plot1_frame,strbuff, Point(plot1_frame.size[1]-100,20), FONT_HERSHEY_SIMPLEX, 0.5, colorArea );
	sprintf(strbuff,"reg:%.1f=%.1fe-3*a+%.1f\0",regresion.curcount,regresion.beta.at<float>(0)*1000,regresion.epsilon.at<float>(0));
	cv::putText(plot1_frame,strbuff, Point(plot1_frame.size[1]/2-50,20), FONT_HERSHEY_SIMPLEX, 0.5, colorReg );
	sprintf(strbuff,"err:%.1f\0",gt_label.curCrossSum-regresion.curcount);
	cv::putText(plot1_frame,strbuff, Point(60,20), FONT_HERSHEY_SIMPLEX, 0.5, errColor );
	cv::resize(plot1_frame,plot1_frameL,Size(plot1_width*2,plot1_height*2),2,2);
	//imshow("plot1",plot1_frame);
	//waitKey(1);
}

void StreamThread::drawItems()
{
	if(gt_label.hasGT)
	{
		gt_label.DrawLabelsFrame(c_frame);
		gt_label.drawLabelsSlice(vid_slice.rgb_buff);
	}
	plot1();
	line(c_frame,Point(pointA[0],pointA[1]), Point(pointB[0],pointB[1]), Scalar(255, 0, 0));
	cv::putText(c_frame, "A", Point(pointA[0],pointA[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0) );
	cv::putText(c_frame, "B", Point(pointB[0],pointB[1]), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0) );
	

}

bool StreamThread::init()
{
	vid_stream=VideoIStream(fnamestr);
	bg_stream=BGModel(bg_path);
	if(vid_width==0||vid_height==0)
	{
		vid_stream.init_VideoIStream(buff_N);
	}
	else{
		vid_stream.init_VideoIStream(vid_width,vid_height,buff_N);
	}
	//vid_stream.initBuffs();	
	if(vid_width==0||vid_height==0)vid_width=vid_stream.width,vid_height=vid_stream.height;
	if(checkPoints())
		pointA[0]=0,pointA[1]=0,pointB[0]=vid_width-1,pointB[1]=vid_height-1;
	
	bg_stream.init_BGStream(vid_width,vid_height,buff_N);
	getLineIdx(line_x,line_y,pointA,pointB);
	vid_slice.init(line_x,line_y,vid_height,vid_width,buff_N);
	bg_slice.init(line_x,line_y,vid_height,vid_width,buff_N);
	features=Feature(buff_N);
	regresion=Regression(buff_N,features);
	gt_label=GTLabel(line_x,line_y,buff_N,"../../data/ucsdData/gtvidf/%06d.txt",100);

	plot1_width=buff_N,plot1_height=200;plot_count_max=100;plot_area_max=10000;plot_reg_max=100;
	usingFrames=true;
	return true;
}
void StreamThread::run()
{
	streaming();
}

void StreamThread::streamStart(string fstr,int l,int h,int w)
{
	QMutexLocker locker(&mutex);
	vid_height=h;
	vid_width=w;
	buff_N=l;
	fnamestr=fstr;
	if (!isRunning()) {
        start(InheritPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
}
