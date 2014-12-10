#include "qt_test.h"

Qt_test::Qt_test(QWidget *parent)
	: QMainWindow(parent)
{
	//qRegisterMetaType<QImage>("QImage");
	//ui.setupUi(this);
	stream_thread=new StreamThread(this);
	createAction();
	selX=0,selY=0;
}
Qt_test::~Qt_test()
{

}

void Qt_test::createAction()
{

	ucsdAct = new QAction(tr("ucsd"), ui.menuBar);
	aviAct = new QAction(tr("avi"), ui.menuBar);
	restartAct = new QAction(tr("restart"), ui.menuBar);
	folderAct = new QAction(tr("openfolder"), ui.menuBar);
	
	connect(ucsdAct,SIGNAL(triggered()),this,SLOT(ucsdclicked()));
	connect(aviAct,SIGNAL(triggered()),this,SLOT(aviClicked()));
	connect(restartAct,SIGNAL(triggered()),this,SLOT(restartClicked()));
	connect(folderAct,SIGNAL(triggered()),this,SLOT(folderClicked()));

	connect(&stream_thread,SIGNAL(debug(const char * )),this,SLOT(debugMsgBox(const char * )),Qt::BlockingQueuedConnection);
	connect(&stream_thread,SIGNAL(aFrameDone()),this,SLOT(updateFrameUI()),Qt::BlockingQueuedConnection);
	connect(&stream_thread,SIGNAL(initUI()),this,SLOT(initUI()),Qt::QueuedConnection);
	connect(ui.videolabel,SIGNAL(leftpressed(int,int)),this,SLOT(setLinePoints(int,int)));
	connect(ui.videolabel,SIGNAL(rightpressed(int,int)),this,SLOT(updatePixLabel(int,int)));
	ui.menuBar->addAction(ucsdAct);
	ui.menuBar->addAction(aviAct);
	ui.menuBar->addAction(restartAct);
	ui.menuBar->addAction(folderAct);
	ui.LineptLabel->setGeometry(280,0,120,30);
	ui.pixelvalLabel->setGeometry(420,0,120,30);
}
void Qt_test::updateFrameUI()
{
	//if(frame_ptr!=NULL)
	//{
		stream_thread.usingFrames=true;
		int vid_w=stream_thread.vid_stream.width,vid_h=stream_thread.vid_stream.height;
		int sli_w=stream_thread.vid_slice.buff_len,sli_h=stream_thread.vid_slice.idx_N;
		//ui.videolabel->setPixmap(QPixmap::fromImage(QImage(frame_ptr,vid_w,vid_h,vid_w,QImage::Format_Indexed8)));
		//ui.slicelabel->setPixmap(QPixmap::fromImage(QImage(stream_thread.vid_slice.data_ptr,sli_w,sli_h,sli_w,QImage::Format_Indexed8)));
		ui.videolabel->setPixmap(QPixmap::fromImage(QImage(stream_thread.c_frame.data,vid_w,vid_h,vid_w*3,QImage::Format_RGB888)));
		ui.bglabel->setPixmap(QPixmap::fromImage(QImage(stream_thread.bg_cframe.data,vid_w,vid_h,vid_w*3,QImage::Format_RGB888)));
		ui.slicelabel->setPixmap(QPixmap::fromImage(QImage(stream_thread.vid_slice.rgb_ptr,sli_w,sli_h,sli_w*3,QImage::Format_RGB888)));
		ui.bgslice->setPixmap(QPixmap::fromImage(QImage(stream_thread.bg_slice.rgb_ptr,sli_w,sli_h,sli_w*3,QImage::Format_RGB888)));
		ui.plot1Label->setPixmap(QPixmap::fromImage(QImage(stream_thread.plot1_frameL.data,stream_thread.plot1_width*2,stream_thread.plot1_height*2,stream_thread.plot1_width*3*2,QImage::Format_RGB888)));

		
		ui.videolabel->repaint();
		ui.slicelabel->repaint();
		ui.bglabel->repaint();
		ui.bgslice->repaint();
		ui.plot1Label->repaint();

		uchar r=stream_thread.c_frame.at<cv::Vec3b>(selY,selX)[0];
		uchar g=stream_thread.c_frame.at<cv::Vec3b>(selY,selX)[1];
		uchar b=stream_thread.c_frame.at<cv::Vec3b>(selY,selX)[2];
		char strbuff[100];
		sprintf(strbuff,"%d,%d;#%0x%0x%0x",selY,selX,r,g,b);
		ui.pixelvalLabel->setText(strbuff);
		ui.pixelvalLabel->repaint();
		stream_thread.usingFrames=false;
	//}
}
void Qt_test::initUI()
{
		int vid_w=stream_thread.vid_stream.width,vid_h=stream_thread.vid_stream.height;
		int sli_w=stream_thread.vid_slice.buff_len,sli_h=stream_thread.vid_slice.idx_N;
		int m = 10;
		ui.videolabel->setGeometry(QRect(m, m, vid_w, vid_h));
		ui.bglabel->setGeometry(QRect(m, m+vid_h+m, vid_w, vid_h));

		ui.slicelabel->setGeometry(QRect(m+vid_w+m, m, sli_w, sli_h));
		ui.bgslice->setGeometry(QRect(m+vid_w+m, m+sli_h+m, sli_w, sli_h));

		ui.plot1Label->setGeometry(QRect(m+vid_w+m, 3*m+sli_h*2, stream_thread.plot1_width*2, stream_thread.plot1_height*2));
		ui.plot1Label->setStyleSheet("background-color: #00f;");

		int window_width=(stream_thread.vid_stream.width+stream_thread.vid_stream.buff_len)+100;
		int window_height= max((stream_thread.vid_slice.idx_N)*2,(stream_thread.vid_stream.height)*2);
		ui.centralWidget->setFixedSize(window_width,window_height);

		ui.videolabel->repaint();
		ui.slicelabel->repaint();
		ui.bglabel->repaint();
		ui.bgslice->repaint();
		ui.plot1Label->repaint();
}
void Qt_test::debugMsgBox(const char * msg)
{
	QMessageBox::question(NULL, "Test", msg,QMessageBox::Ok);
}
void Qt_test::ucsdclicked()
{
	selY=0;selX=0;
	stream_thread.hasGT=true;
	filename="../../data/ucsdData/videoDir/%06d.png";
	//stream_thread.bg_path="../../data/ucsdData/segmDir/%06d.png";
	stream_thread.streamStart(filename.toStdString(),500,158,238);
}
void Qt_test::folderClicked()
{
	selY=0;selX=0;
	stream_thread.hasGT=false;
	QString dlgfilename = QFileDialog::getOpenFileName(this,tr("Open Image"), "../../data/", tr("Video Files (*.jpg *.png *.bmp)"));
	if(!dlgfilename.isEmpty())
	{
		filename=dlgfilename;
		QString dir=filename.left(filename.lastIndexOf("/")+1);
		//stream_thread.bg_path=(dir+"bg/%06d.png").toStdString();
		filename=dir+"%06d.png";
		stream_thread.streamStart(filename.toStdString(),500,540,720);
	}
}
void Qt_test::aviClicked()
{
	selY=0;selX=0;
	stream_thread.hasGT=false;
	//if(filename.isEmpty())
	QString dlgfilename = QFileDialog::getOpenFileName(this,tr("Open Image"), "../../data/", tr("Video Files (*.avi *.mp4 *.mkv)"));
	if(!dlgfilename.isEmpty())
	{
		filename=dlgfilename;
		QString dir=filename.left(filename.lastIndexOf("/")+1);
		stream_thread.bg_path=(dir+"bg/%06d.png").toStdString();
		stream_thread.streamStart(filename.toStdString(),500);
	}
}
void Qt_test::restartClicked()
{
	if(!filename.isEmpty())
	{
		//QString dir=filename.left(filename.lastIndexOf("/")+1);
		//stream_thread.bg_path=(dir+"bg/%06d.png").toStdString();
		
		if(stream_thread.vid_stream.isVid)
			stream_thread.streamStart(filename.toStdString(),500);
		else
			stream_thread.streamStart(filename.toStdString(),500,158,238);
	}
}


void Qt_test::setLinePoints(int x ,int y)
{
	static bool k=true;
	if(k)
	{
	stream_thread.pointA[0]=x;
	stream_thread.pointA[1]=y;
	}
	else
	{
	stream_thread.pointB[0]=x;
	stream_thread.pointB[1]=y;
	}
	k=!k;
	updateLine();
}
void Qt_test::updateLine()
{
	char strbuff[100];
	sprintf(strbuff,"A:%d,%d;B:%d,%d\0",stream_thread.pointA[0],stream_thread.pointA[1],stream_thread.pointB[0],stream_thread.pointB[1]);
	ui.LineptLabel->setText(strbuff);
	ui.LineptLabel->repaint();
}

void Qt_test::updatePixLabel(int x,int y)
{
	selX=x,selY=y;
	if(selY>=stream_thread.vid_height)selY=1;if(selX>=stream_thread.vid_width)selX=1;
	uchar r=stream_thread.c_frame.at<cv::Vec3b>(y,x)[0];
	uchar g=stream_thread.c_frame.at<cv::Vec3b>(y,x)[1];
	uchar b=stream_thread.c_frame.at<cv::Vec3b>(y,x)[2];
	char strbuff[100];
	sprintf(strbuff,"%0x",r);
	ui.pixelvalLabel->setText(strbuff);
	ui.pixelvalLabel->repaint();

}