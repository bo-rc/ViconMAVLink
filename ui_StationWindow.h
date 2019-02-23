/********************************************************************************
** Form generated from reading UI file 'StationWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONWINDOW_H
#define UI_STATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationWindow
{
public:
    QAction *actionConnect_Vicon;
    QAction *actionDisconnect_Vicon;
    QAction *actionQuit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QComboBox *NorthMapComboBox;
    QLineEdit *hostPortLine;
    QLineEdit *viconGPSLine;
    QLabel *label_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;
    QWidget *page_2;
    QLabel *hostAddressLabel;
    QLabel *hostPortLabel;
    QLineEdit *hostAddressLine;
    QLabel *label;
    QLabel *NothLabel;
    QPushButton *startMavLinkSenderButton;
    QLabel *dtLabel;
    QLabel *status;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StationWindow)
    {
        if (StationWindow->objectName().isEmpty())
            StationWindow->setObjectName(QString::fromUtf8("StationWindow"));
        StationWindow->resize(379, 516);
        actionConnect_Vicon = new QAction(StationWindow);
        actionConnect_Vicon->setObjectName(QString::fromUtf8("actionConnect_Vicon"));
        actionDisconnect_Vicon = new QAction(StationWindow);
        actionDisconnect_Vicon->setObjectName(QString::fromUtf8("actionDisconnect_Vicon"));
        actionQuit = new QAction(StationWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(StationWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        NorthMapComboBox = new QComboBox(centralWidget);
        NorthMapComboBox->setObjectName(QString::fromUtf8("NorthMapComboBox"));

        gridLayout->addWidget(NorthMapComboBox, 6, 3, 1, 1);

        hostPortLine = new QLineEdit(centralWidget);
        hostPortLine->setObjectName(QString::fromUtf8("hostPortLine"));

        gridLayout->addWidget(hostPortLine, 3, 3, 1, 1);

        viconGPSLine = new QLineEdit(centralWidget);
        viconGPSLine->setObjectName(QString::fromUtf8("viconGPSLine"));

        gridLayout->addWidget(viconGPSLine, 6, 0, 1, 3);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        listWidget = new QListWidget(page);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_2->addWidget(listWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 8, 0, 2, 4);

        hostAddressLabel = new QLabel(centralWidget);
        hostAddressLabel->setObjectName(QString::fromUtf8("hostAddressLabel"));

        gridLayout->addWidget(hostAddressLabel, 2, 0, 1, 1);

        hostPortLabel = new QLabel(centralWidget);
        hostPortLabel->setObjectName(QString::fromUtf8("hostPortLabel"));

        gridLayout->addWidget(hostPortLabel, 2, 3, 1, 1);

        hostAddressLine = new QLineEdit(centralWidget);
        hostAddressLine->setObjectName(QString::fromUtf8("hostAddressLine"));

        gridLayout->addWidget(hostAddressLine, 3, 0, 1, 3);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 0, 1, 2);

        NothLabel = new QLabel(centralWidget);
        NothLabel->setObjectName(QString::fromUtf8("NothLabel"));

        gridLayout->addWidget(NothLabel, 4, 3, 1, 1);

        startMavLinkSenderButton = new QPushButton(centralWidget);
        startMavLinkSenderButton->setObjectName(QString::fromUtf8("startMavLinkSenderButton"));

        gridLayout->addWidget(startMavLinkSenderButton, 10, 0, 1, 1);

        dtLabel = new QLabel(centralWidget);
        dtLabel->setObjectName(QString::fromUtf8("dtLabel"));
        dtLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(dtLabel, 0, 1, 1, 1);

        status = new QLabel(centralWidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(status, 0, 0, 1, 1);

        StationWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StationWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 379, 25));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        StationWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StationWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMouseTracking(true);
        StationWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StationWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        StationWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionConnect_Vicon);
        menuMenu->addAction(actionDisconnect_Vicon);
        menuMenu->addAction(actionQuit);

        retranslateUi(StationWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StationWindow)
    {
        StationWindow->setWindowTitle(QApplication::translate("StationWindow", "ViconMAVLink", 0, QApplication::UnicodeUTF8));
        actionConnect_Vicon->setText(QApplication::translate("StationWindow", "Connect Vicon", 0, QApplication::UnicodeUTF8));
        actionDisconnect_Vicon->setText(QApplication::translate("StationWindow", "Disconnect Vicon", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("StationWindow", "Quit", 0, QApplication::UnicodeUTF8));
        NorthMapComboBox->clear();
        NorthMapComboBox->insertItems(0, QStringList()
         << QApplication::translate("StationWindow", "+x", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StationWindow", "-x", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StationWindow", "+y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("StationWindow", "-y", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("StationWindow", "Captured Objects:", 0, QApplication::UnicodeUTF8));
        hostAddressLabel->setText(QApplication::translate("StationWindow", "HostAddress:", 0, QApplication::UnicodeUTF8));
        hostPortLabel->setText(QApplication::translate("StationWindow", "HostPort:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StationWindow", "GPS Coordinates of Vicon Origin:", 0, QApplication::UnicodeUTF8));
        NothLabel->setText(QApplication::translate("StationWindow", "North:", 0, QApplication::UnicodeUTF8));
        startMavLinkSenderButton->setText(QApplication::translate("StationWindow", "Start a MavLink Sender", 0, QApplication::UnicodeUTF8));
        dtLabel->setText(QApplication::translate("StationWindow", "dt", 0, QApplication::UnicodeUTF8));
        status->setText(QApplication::translate("StationWindow", "status", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("StationWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StationWindow: public Ui_StationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONWINDOW_H
