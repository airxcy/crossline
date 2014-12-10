#include "cvClasses.h"
char errstrbuff[100];
void cv_debug(string errstrbuff)
{
	Mat errormat(60,300,CV_8UC3);
	putText(errormat,errstrbuff,Point(0,30),FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,255));
	imshow("debug",errormat);
	waitKey(0);
}
int getLineIdx(std::vector<int>& x_idx,std::vector<int>& y_idx,int* PointA,int* PointB)
{
	int line_len=0,idx_N=0;
	Point start=Point(PointA[0],PointA[1]);
	Point end=Point(PointB[0],PointB[1]);
	if(start.y>end.y)
	{
		Point tmppnt=start;
		start=end;
		end=tmppnt;
	}
	if(start.x==end.x)
	{
		line_len=end.y-start.y;
		idx_N=end.y-start.y;

		x_idx = std::vector<int>(idx_N,start.x);
		y_idx = std::vector<int>(idx_N);
		for(int i=start.y,j=0;i < end.y;i++,j++)
		{
			y_idx[j]=i;
		}
		return 1;
	}
	else
	{
		int dx,dy,err,thresherr;
		int diffx=std::abs(end.x-start.x),diffy=std::abs(end.y-start.y);
		if(end.y>start.y)dy=1;
		else if (end.y<start.y)dy=-1;
		else dy=0;
		if(end.x>start.x)dx=1;
		else if (end.x<start.x)dx=-1;
		else dx=0;
		int x=start.x,y=start.y,step,incre;
		int *increter,*steper;
		if(diffx>diffy)
		{
			err=diffy;
			thresherr=diffx/2;
			increter=&y;
			incre=dy;
			steper=&x;
			step=dx;
			line_len=diffy;
			idx_N=diffx;
		}
		else if (diffx<diffy)
		{
			err=diffx;
			thresherr=diffy/2;
			increter=&x;
			incre=dx;
			steper=&y;
			step=dy;
			line_len=diffy;
			idx_N=diffy;
		}
		x_idx = std::vector<int>(idx_N);
		y_idx = std::vector<int>(idx_N);
		int toterr=err;
		for(int i=0;i<idx_N;i++)
		{
			x_idx[i]=x;
			y_idx[i]=y;
			(*steper)+=step;
			toterr+=err;
			if((toterr)>thresherr)
			{
				toterr=toterr-idx_N;
				(*increter)+=incre;
			}
		}
		return 1;
	}
	
}
VideoIStream::VideoIStream(){}
VideoIStream::~VideoIStream(){}
VideoIStream::VideoIStream(std::string fname)
{
	fname_str=string(fname);
}
bool VideoIStream::init_VideoIStream(int l)
{
	vid_cpt=VideoCapture(fname_str);
	if(vid_cpt.isOpened())
	{
		width=vid_cpt.get(CV_CAP_PROP_FRAME_WIDTH);
		height=vid_cpt.get(CV_CAP_PROP_FRAME_HEIGHT);
		buff_len=l;
		isVid=true;
		return true;
	}
	else
		return false;
}
bool VideoIStream::init_VideoIStream(int w,int h,int l)
{
	/*
	vid_cpt=VideoCapture(fname_str);
	if(vid_cpt.isOpened())
	{
		width=w;
		height=h;
		buff_len=l;
		return true;
	}
	else
		return false;
	*/
	
	const char* fnamestring = fname_str.c_str();
	frameidx=0;
	sprintf(strbuff,fnamestring,frameidx);
	Mat initImg = imread(strbuff);
	if (initImg.empty())
	{
		frameidx++;
		sprintf(strbuff,fnamestring,frameidx);
		initImg = imread(strbuff);
	}
	if(!initImg.empty())
	{
		height=initImg.size[0];
		width=initImg.size[1];
		buff_len=l;
		isVid=false;
		return true;
	}
	else
		return false;
}
void VideoIStream::initBuffs()
{
	int volumesize[3]={buff_len,height,width};
	video_buff = Mat(3,volumesize,IMGTYPE);
	headidx=0;tailidx=0;
	frame_byte_size=height*width;
	headptr=video_buff.data+headidx*frame_byte_size;
	tailptr=video_buff.data+tailidx*frame_byte_size;
	cur_frame_ptr=tailptr;
}
bool VideoIStream::readFrame(Mat& frame)
{
	if(isVid)
	{
		vid_cpt.grab();
		return vid_cpt.retrieve( frame, 3);
	}
	else
	{
		sprintf(strbuff,fname_str.c_str(),frameidx);
		frame = imread(strbuff,1);
		frameidx++;
		//while(frame.empty())
		//{
		//	sprintf(strbuff,fname_str.c_str(),frameidx);
		//	frame = imread(strbuff,1);
		//	frameidx++;
		//}
		return !frame.empty();
	}
}
void VideoIStream::updateBuff(unsigned char* new_frame_ptr)
{
	if (video_buff.empty())
		initBuffs();
	memcpy(tailptr,new_frame_ptr,frame_byte_size);
	tailidx=(tailidx+1)%buff_len;
	if(tailidx==headidx)
	{
		headidx=(headidx+1)%buff_len;
	}
	cur_frame_ptr=tailptr;
	headptr=video_buff.data+headidx*frame_byte_size;
	tailptr=video_buff.data+tailidx*frame_byte_size;
}
bool VideoIStream::releaseStream()
{
	 vid_cpt.release();
	 return vid_cpt.isOpened();
}


LineSlice::LineSlice(){};
LineSlice::~LineSlice(){};

int LineSlice::init(std::vector<int>& x,std::vector<int>& y,int h,int w,int l)
{
	width=w;
	height=h;
	buff_len=l;
	x_idx=x;
	y_idx=y;
	idx_N=x.size();
	line_len=x.size();
	data_buff=Mat::zeros(idx_N,buff_len,IMGTYPE);
	rgb_buff=Mat::zeros(idx_N,buff_len,CV_8UC3);
	rgb_ptr=rgb_buff.data;
	data_ptr=data_buff.data;
	tail_ptr=data_ptr;
	tail_idx=0;
	return 1;
}

void LineSlice::fromAFrame(unsigned char* frameptr)
{
	//if(data_buff.empty())init(80,0,80,158,158,238,1000);
	unsigned char* ptr=data_ptr;
	if(tail_idx==buff_len)
	{
		//shift buffer one place
		for(int i=0;i<idx_N;i++)
		{
			memmove(ptr,ptr+1,buff_len-1);
			ptr+=buff_len;
		}
		ptr=data_ptr+buff_len-1;
	}
	else
	{
		ptr=data_ptr+tail_idx;
		tail_idx++;
	}
	for(int i=0;i<idx_N;i++)
	{
		*ptr=*(frameptr+y_idx[i]*width+x_idx[i]);
		ptr+=buff_len;
		*(frameptr+y_idx[i]*width+x_idx[i])=255;
	}
	cvtColor(data_buff,rgb_buff,CV_GRAY2RGB);
}

bool BGModel::init_BGStream(int l)
{
	if(!init_VideoIStream(l))
	{
		noGT=true;
		initpMOG();
		return true;
	}
}
bool BGModel::init_BGStream(int w,int h,int l)
{
	if(!init_VideoIStream(w,h,l))
	{
		noGT=true;
		initpMOG();
		return true;
	}
}
void BGModel::initpMOG()
{
		pMOG =  BackgroundSubtractorMOG2();
		//pMOG.initialize(Size(width,height),CV_8UC1);
		//pMOG.set("fTau",0);
}
bool BGModel::getBgMask(Mat& frame,Mat& fmask)
{
	
	if(noGT)
	{
		pMOG(frame,fmask);
	}
	else
	{
		const char* fnamestring = fname_str.c_str();
		sprintf(strbuff,fnamestring,frameidx);
		fmask = imread(strbuff,0);
		frameidx++;
		while(fmask.empty())
		{
			sprintf(strbuff,fnamestring,frameidx);
			fmask = imread(strbuff,0);
			frameidx++;
		}
	}
	return true;
}

int GTLabel::loadXYIdx(int fi)
{
	
	char strbuff[100];
	string line;
	float x,y;
	int idx;
	sprintf(strbuff,"../../data/ucsdData/gtvidf/%06d.txt",fi);
	std::ifstream myfile(strbuff);
	int counter=0;
	if(myfile.is_open())
	{
		pplN[tail]=0;
		while(getline(myfile,line))
		{
			int offset = tail*max_ppl+pplN[tail];
			sscanf(line.c_str(),"%f,%f,%d",locX+offset,locY+offset,ppl_idx+offset);
			pplN[tail]++;
			counter++;
		}
		myfile.close();
		hasGT=true;
	}
	else
	{
		hasGT=false;
		return -1;
		
	}
	frameidx[tail]=fi;
	
	tail=(tail+1)%buff_len;
	if(tail==head)head=(head+1)%buff_len;
	else que_len++;
	updateGTCross();
	return counter;
}

bool GTLabel::DrawLabelsFrame(Mat& frame)
{
	
	if(que_len<1)return false;
	int curidx=((tail+buff_len)-1)%buff_len;
	for(int i=0;i<pplN[curidx];i++)
	{
		//circle(frame, Point(100,100), 2, Scalar(0,255,0), 2, 8, 0);
		int offset = curidx*max_ppl+i;
		int x=*(locX+offset),y=*(locY+offset),idx=*(ppl_idx+offset);
		circle(frame, Point(x,y), 2, Scalar(0,255,0), 2, 8, 0);
		putText(frame,std::to_string(idx),Point(x,y),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,0,0));
	}
	return true;
}
bool checkIntersect()
{
	return true;
}
bool GTLabel::updateGTCross()
{
	
	bool crossed=false;
	float startx=line_x[0],starty=line_y[0],endx=line_x[idx_N-1],endy=line_y[idx_N-1];
	int stepback=1;
	int curidx=((tail+buff_len)-1)%buff_len,preidx=((curidx+buff_len)-stepback)%buff_len;
	if(que_len<stepback+1)return false;
	
	float normy=startx-endx,normx=-(starty-endy);
	cross_N[cross_tail]=0;
	for(int i=0;i<pplN[curidx];i++)
	{
		int curoffset = curidx*max_ppl+i;
		int cur_person_idx=ppl_idx[curoffset];

		for(int j=0;j<pplN[preidx];j++)
		{
			int preoffset = preidx*max_ppl+j;
			int pre_person_idx=ppl_idx[preoffset];

			if(cur_person_idx==pre_person_idx)
			{
				
				float valcur = normx*(locX[curoffset]-startx)+normy*(locY[curoffset]-starty);
				float valpre = normx*(locX[preoffset]-startx)+normy*(locY[preoffset]-starty);

				if(valcur*valpre<=0)
				{
					float normlen = (endx-startx)*(endx-startx)+(endy-starty)*(endy-starty);
					float project=((locX[curoffset]-startx)*(endx-startx)+(locY[curoffset]-starty)*(endy-starty))/normlen;
					
					if (project>=0 && project<1)
					{
						
						int crosspos=project*idx_N;
						int cross_offset=cross_tail*max_ppl+cross_N[cross_tail];
						cross_idx[cross_offset]=cur_person_idx;
						cross_pos[cross_offset]=crosspos;
						cross_N[cross_tail]++;
					}
				}
			}
		}
	}
	curCrossSum=sum(cross_N)[0];

	crossedSum[cross_tail]=curCrossSum;
	cross_tail=(cross_tail+1)%buff_len;
	if(cross_tail==cross_head)cross_head=(cross_head+1)%buff_len;
	//cross_N[cross_tail]=0;

	return true;
}
void GTLabel::drawLabelsSlice(Mat& frame)
{
	int xpos=0;
	int i=cross_head;
	do
	//for(int i=cross_tail;i
	{
		for(int j=0;j<cross_N[i];j++)
		{
			int cross_offset=i*max_ppl+j;
			circle(frame, Point(xpos,cross_pos[cross_offset]), 1, Scalar(0,255,0), 2, 8, 0);
			//frame.at<cv::Vec3b>(Point(xpos,cross_pos[cross_offset]))=cv::Vec3b(0,255,0);
		}
		xpos++;
		i=(i+1)%buff_len;
	}while(i!=cross_head);
}
void Feature::updateFeatCount(int count)
{
	featset[feat_N*dim+0]=curArea;
	countset[feat_N]=(float)count;
	feat_N++;
	if(feat_N>=cur_Size)
	{
		
		cur_Size=cur_Size*2;
		float* tmpptr=(float*)realloc(featset,cur_Size*dim*sizeof(float));
		//free (featset);
		featset = tmpptr;
		
		tmpptr=(float*)realloc(countset,cur_Size*sizeof(float));
		
		//free (countset);
		countset = tmpptr;
	}
	
	Mat tmpMat = Mat(1,feat_N,CV_32F,countset);
	cmean = mean(tmpMat);
	variance =tmpMat-cmean;
	meanvar = mean(variance)[0];
	cv::pow(variance,2,variance);
	cv::sqrt(sum(variance),stdDev);
	
}
void Feature::updateFeat(Mat& bg_slice)
{
	curArea=countNonZero(bg_slice)+1;
	curfeat[0]=curArea;
	areavect[tail]=curArea;
	tail=(tail+1)%buff_len;
	if(tail==head)head=(head+1)%buff_len;
}
void Regression::IDLinear(Feature &feat)
{
	//count =area*k+b;
	
	Mat x(1,feat.dim,CV_32F,feat.curfeat);
	
	Mat countMat=(x*beta)+epsilon;

	curcount = countMat.at<float>(0);
	//cv_debug("here");
	countvec[tail]=curcount;
	tail=(tail+1)%buff_len;
	if(tail==head)head=(head+1)%buff_len;
}
void Regression::updateIDLinear(Feature &feat)
{
	//k= (count-b)/k;
	Mat X(feat.feat_N,feat.dim,CV_32F,feat.featset);
	Mat y(feat.feat_N,1,CV_32F,feat.countset);
	if(sum(X)[0]>0)
	{
		Mat regval= (X.t()*X).inv()*X.t()*y;
		beta.at<float>(0)=regval.at<float>(0);
		regval=(y-X*beta);
		epsilon.at<float>(0)=regval.at<float>(0);
		//cv_debug("done");
		
	}
}
