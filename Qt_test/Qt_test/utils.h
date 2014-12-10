#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

#define imgType CV_8UC1
#define imgTypeC CV_8UC4

void lineSampling(Mat& slice,Mat volume,int linepos);
void featureExtraction(Mat& featvec,Mat vidSlice,Mat segSlice,Mat binSlice,Mat Wv,Mat Wp);
void linearRegression(Mat& Beta,Mat X,Mat& y);
void insCount(Mat& s,Mat n,int frameN,int L);
void getHistIdx(Mat& HistIdx,Mat edgeHist[],Mat periImg,Mat Gfilter[]);
void globalFeature(float* featvec,Mat vidSlice,Mat segSlice,Mat binSlice,Mat Wv,Mat Wp);
void caliSpace(Mat& spaceWMap, Mat video, int frameAidx, int frameBidx);
void loadbinFile(Mat& mat,string fname);
void gettempWeight(Mat& tempWMapt,int linepos,Mat video);
void loadVideoFromImgs(Mat& volume, const string& dir,const string& fext,int startidx,int endidx,int height,int width);
void viewvideo(string windowname,Mat video);