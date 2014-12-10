
#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
#include <qimage.h>
#include "cvClasses.h"
//#include "qt_test.h"
class StreamThread : public QThread
{
	Q_OBJECT
public:
	//StreamThread(){};
	StreamThread(QObject *parent = 0);
	~StreamThread();
	
	
	void streaming();
	bool checkPoints();
	void drawItems();
	void plot1();
	void cleanUpFrames();
public:
	char strbuff[100];
	//videos and background
	std::string fnamestr;
	std::string bg_path;
	int vid_height;
	int vid_width;
	int buff_N;
	VideoIStream vid_stream;
	BGModel bg_stream;
	

	//Line Sampling
	int pointA[2],pointB[2];
	std::vector<int> line_x,line_y;
	LineSlice vid_slice;
	LineSlice bg_slice;

	//Feature
	Feature features;
	//regression
	Regression regresion;
	//float fcount;
	
	//gt
	bool hasGT;
	GTLabel gt_label;
	



	//plot
	float plot_count_max;
	float plot_area_max;
	float plot_reg_max;
	int plot1_width,plot1_height;
	Mat plot1_frame;
	Mat plot1_frameL;

	Mat a_frame;
	Mat c_frame;
	Mat bg_cframe;
	Mat bg_frame;
	bool usingFrames;

public slots:
	void streamStart(string fstr,int l,int h=0,int w=0);
	bool init();
	//void setPointA();
signals:
	void aFrameDone();
	void debug(const char * msg);
	void initUI();
protected:
	
	void run();
	//void run(Ui::Qt_testClass ui);

public:
	QMutex mutex;
	QWaitCondition condition;
	bool restart;
    bool abort;
	//StreamThread( const StreamThread& other );
	StreamThread &  operator= (  const StreamThread & newStreamthread );
};