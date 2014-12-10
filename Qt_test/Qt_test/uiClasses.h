
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

#include <QtWidgets/qtoolbutton>
#include <QMouseEvent>
#include <QFileDialog>
#include <QString>
#include <QScrollArea>

class frameLabel: public QLabel
{
	Q_OBJECT
public:
	frameLabel(QWidget * parent = 0):QLabel ( parent )
	{
	}

	int mousex,mousey;
protected:
	virtual void mousePressEvent(QMouseEvent * ev);
	virtual void mouseReleaseEvent(QMouseEvent * ev);
signals:
	void leftpressed(int x,int y);
	void rightpressed(int x,int y);
	void leftreleased(int x,int y);
};

class QtUiClass
{
public:
	QWidget *centralWidget;
	QScrollArea *scrollArea;

	frameLabel* videolabel;
	frameLabel* slicelabel;
	frameLabel* bglabel;
	frameLabel* bgslice;
	frameLabel* plot1Label;

	QLabel* LineptLabel;
	QLabel* pixelvalLabel;
	QMenuBar *menuBar;
    QStatusBar *statusBar;


	void setupUi(QMainWindow *Qt_testClass)
	{
		if (Qt_testClass->objectName().isEmpty())
            Qt_testClass->setObjectName(QStringLiteral("Qt_testClass"));
        Qt_testClass->resize(600, 400);
        centralWidget = new QWidget(Qt_testClass);

		scrollArea = new QScrollArea(Qt_testClass);
		scrollArea->setObjectName(QStringLiteral("scrollArea"));
		scrollArea->setWidget(centralWidget);
		Qt_testClass->setCentralWidget(scrollArea);
		

        videolabel = new frameLabel(scrollArea);
        videolabel->setObjectName(QStringLiteral("videolabel"));
        videolabel->setGeometry(QRect(10, 10, 151, 111));
        slicelabel = new frameLabel(scrollArea);
        slicelabel->setObjectName(QStringLiteral("slicelabel"));
        slicelabel->setGeometry(QRect(190, 10, 381, 111));
        bglabel = new frameLabel(scrollArea);
        bglabel->setObjectName(QStringLiteral("bglabel"));
        bglabel->setGeometry(QRect(10, 120, 151, 111));
		bgslice =new frameLabel(scrollArea);
		bgslice->setObjectName(QStringLiteral("bgslice"));
		bgslice->setGeometry(QRect(190, 120, 381, 111));
		plot1Label= new frameLabel(scrollArea);
        plot1Label->setObjectName(QStringLiteral("plot1Label"));
        plot1Label->setGeometry(QRect(370, 120, 381, 111));
       
        menuBar = new QMenuBar(Qt_testClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        Qt_testClass->setMenuBar(menuBar);

		LineptLabel = new QLabel(menuBar);
		LineptLabel->setAlignment(Qt::AlignCenter);
		LineptLabel->setStyleSheet("background-color: #789;");

		pixelvalLabel = new QLabel(menuBar);
		pixelvalLabel->setAlignment(Qt::AlignCenter);
		pixelvalLabel->setStyleSheet("background-color: #cba;");

        statusBar = new QStatusBar(Qt_testClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_testClass->setStatusBar(statusBar);
		


        retranslateUi(Qt_testClass);

        QMetaObject::connectSlotsByName(Qt_testClass);
	}

	void retranslateUi(QMainWindow *Qt_testClass)
    {
        Qt_testClass->setWindowTitle(QApplication::translate("Qt_testClass", "Qt_test", 0));
        videolabel->setText(QString());
        slicelabel->setText(QString());
    } // retranslateUi
};


