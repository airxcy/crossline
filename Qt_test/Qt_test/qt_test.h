#ifndef QT_TEST_H
#define QT_TEST_H

#include <QtWidgets/QMainWindow>


#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <iostream>

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif
//#include"uiClasses.h"
//#include "ui_qt_test.h"
//#include "cvClasses.h"
#include "StreamThread.h"

class Qt_test : public QMainWindow
{
	Q_OBJECT

public:
	Qt_test(QWidget *parent = 0);
	~Qt_test();
	
	//unsigned char* getOrderSlice();
	
	QString filename;
	//Ui::Qt_testClass ui;
	//QtUiClass ui;
	int selX,selY;

	void updateLine();
	void createAction();

	StreamThread stream_thread;
	//VideoIStream vid_stream;
	//LineSlice vid_slice;
public slots:
	//void startStream();
	void updateFrameUI();
	void debugMsgBox(const char * msg);
	void ucsdclicked();
	void initUI();
	void setLinePoints(int,int);
	void folderClicked();
	void aviClicked();
	void restartClicked();
	void updatePixLabel(int x,int y);
signals:
	void startusdc();
	void smthing(const char * msg);
public:
	QAction *ucsdAct;
	QAction *aviAct;
	QAction *restartAct;
	QAction *folderAct;
	//QAction *drawLineAct; 

};

#endif // QT_TEST_H
