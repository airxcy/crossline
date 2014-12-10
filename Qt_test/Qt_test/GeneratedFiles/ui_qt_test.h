/********************************************************************************
** Form generated from reading UI file 'qt_test.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_TEST_H
#define UI_QT_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_testClass
{
public:
    QWidget *centralWidget;
    QLabel *videolabel;
    QLabel *slicelabel;
    QLabel *bglabel;
    QMenuBar *menuBar;
    QMenu *menuAdd;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Qt_testClass)
    {
        if (Qt_testClass->objectName().isEmpty())
            Qt_testClass->setObjectName(QStringLiteral("Qt_testClass"));
        Qt_testClass->resize(600, 400);
        centralWidget = new QWidget(Qt_testClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        videolabel = new QLabel(centralWidget);
        videolabel->setObjectName(QStringLiteral("videolabel"));
        videolabel->setGeometry(QRect(10, 10, 151, 111));
        slicelabel = new QLabel(centralWidget);
        slicelabel->setObjectName(QStringLiteral("slicelabel"));
        slicelabel->setGeometry(QRect(190, 10, 381, 111));
        bglabel = new QLabel(centralWidget);
        bglabel->setObjectName(QStringLiteral("bglabel"));
        bglabel->setGeometry(QRect(10, 120, 151, 131));
        Qt_testClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qt_testClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuAdd = new QMenu(menuBar);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        Qt_testClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(Qt_testClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_testClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(Qt_testClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(0, 0));
        Qt_testClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuAdd->menuAction());

        retranslateUi(Qt_testClass);

        QMetaObject::connectSlotsByName(Qt_testClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_testClass)
    {
        Qt_testClass->setWindowTitle(QApplication::translate("Qt_testClass", "Qt_test", 0));
        videolabel->setText(QString());
        slicelabel->setText(QString());
        bglabel->setText(QApplication::translate("Qt_testClass", "TextLabel", 0));
        menuAdd->setTitle(QApplication::translate("Qt_testClass", "add", 0));
    } // retranslateUi

};

namespace Ui {
    class Qt_testClass: public Ui_Qt_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H
