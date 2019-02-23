/********************************************************************************
** Form generated from reading UI file 'SenderWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDERWINDOW_H
#define UI_SENDERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "qwt_slider.h"

QT_BEGIN_NAMESPACE

class Ui_SenderWindow
{
public:
    QGridLayout *gridLayout;
    QCheckBox *viconCheckBox;
    QLabel *remoteIPlabel;
    QLabel *compIDlabel;
    QPushButton *start;
    QSpacerItem *verticalSpacer;
    QLabel *droneNameLabel;
    QwtSlider *rateSlider;
    QLineEdit *remoteIPLine;
    QCheckBox *localPosCheckBox;
    QLineEdit *compIDLine;
    QLineEdit *sysIDLine;
    QLabel *MotionCaptureLabel;
    QLineEdit *remotePortLine;
    QLabel *Ratelabel;
    QPushButton *stop;
    QLabel *remotePortLabel;
    QLabel *SysIDLabel;
    QCheckBox *gpsCheckBox;
    QLabel *locPosLabel;

    void setupUi(QWidget *SenderWindow)
    {
        if (SenderWindow->objectName().isEmpty())
            SenderWindow->setObjectName(QString::fromUtf8("SenderWindow"));
        SenderWindow->resize(437, 323);
        gridLayout = new QGridLayout(SenderWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        viconCheckBox = new QCheckBox(SenderWindow);
        viconCheckBox->setObjectName(QString::fromUtf8("viconCheckBox"));

        gridLayout->addWidget(viconCheckBox, 8, 0, 1, 3);

        remoteIPlabel = new QLabel(SenderWindow);
        remoteIPlabel->setObjectName(QString::fromUtf8("remoteIPlabel"));

        gridLayout->addWidget(remoteIPlabel, 2, 0, 1, 1);

        compIDlabel = new QLabel(SenderWindow);
        compIDlabel->setObjectName(QString::fromUtf8("compIDlabel"));

        gridLayout->addWidget(compIDlabel, 5, 0, 1, 1);

        start = new QPushButton(SenderWindow);
        start->setObjectName(QString::fromUtf8("start"));

        gridLayout->addWidget(start, 9, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        droneNameLabel = new QLabel(SenderWindow);
        droneNameLabel->setObjectName(QString::fromUtf8("droneNameLabel"));

        gridLayout->addWidget(droneNameLabel, 0, 3, 1, 1);

        rateSlider = new QwtSlider(SenderWindow);
        rateSlider->setObjectName(QString::fromUtf8("rateSlider"));
        QFont font;
        font.setPointSize(9);
        font.setItalic(false);
        rateSlider->setFont(font);
        rateSlider->setLowerBound(2);
        rateSlider->setScaleMaxMajor(1);
        rateSlider->setScaleMaxMinor(1);
        rateSlider->setScaleStepSize(20);
        rateSlider->setSingleSteps(2u);
        rateSlider->setWrapping(false);
        rateSlider->setInvertedControls(false);
        rateSlider->setOrientation(Qt::Horizontal);
        rateSlider->setGroove(false);

        gridLayout->addWidget(rateSlider, 6, 2, 2, 2);

        remoteIPLine = new QLineEdit(SenderWindow);
        remoteIPLine->setObjectName(QString::fromUtf8("remoteIPLine"));

        gridLayout->addWidget(remoteIPLine, 2, 1, 1, 3);

        localPosCheckBox = new QCheckBox(SenderWindow);
        localPosCheckBox->setObjectName(QString::fromUtf8("localPosCheckBox"));

        gridLayout->addWidget(localPosCheckBox, 7, 0, 1, 2);

        compIDLine = new QLineEdit(SenderWindow);
        compIDLine->setObjectName(QString::fromUtf8("compIDLine"));

        gridLayout->addWidget(compIDLine, 5, 1, 1, 1);

        sysIDLine = new QLineEdit(SenderWindow);
        sysIDLine->setObjectName(QString::fromUtf8("sysIDLine"));

        gridLayout->addWidget(sysIDLine, 4, 1, 1, 1);

        MotionCaptureLabel = new QLabel(SenderWindow);
        MotionCaptureLabel->setObjectName(QString::fromUtf8("MotionCaptureLabel"));

        gridLayout->addWidget(MotionCaptureLabel, 0, 0, 1, 2);

        remotePortLine = new QLineEdit(SenderWindow);
        remotePortLine->setObjectName(QString::fromUtf8("remotePortLine"));

        gridLayout->addWidget(remotePortLine, 3, 1, 1, 2);

        Ratelabel = new QLabel(SenderWindow);
        Ratelabel->setObjectName(QString::fromUtf8("Ratelabel"));
        Ratelabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Ratelabel, 8, 3, 1, 1);

        stop = new QPushButton(SenderWindow);
        stop->setObjectName(QString::fromUtf8("stop"));

        gridLayout->addWidget(stop, 10, 0, 1, 1);

        remotePortLabel = new QLabel(SenderWindow);
        remotePortLabel->setObjectName(QString::fromUtf8("remotePortLabel"));

        gridLayout->addWidget(remotePortLabel, 3, 0, 1, 1);

        SysIDLabel = new QLabel(SenderWindow);
        SysIDLabel->setObjectName(QString::fromUtf8("SysIDLabel"));

        gridLayout->addWidget(SysIDLabel, 4, 0, 1, 1);

        gpsCheckBox = new QCheckBox(SenderWindow);
        gpsCheckBox->setObjectName(QString::fromUtf8("gpsCheckBox"));

        gridLayout->addWidget(gpsCheckBox, 6, 0, 1, 1);

        locPosLabel = new QLabel(SenderWindow);
        locPosLabel->setObjectName(QString::fromUtf8("locPosLabel"));

        gridLayout->addWidget(locPosLabel, 10, 1, 1, 3);

        remotePortLabel->raise();
        remotePortLine->raise();
        gpsCheckBox->raise();
        MotionCaptureLabel->raise();
        start->raise();
        localPosCheckBox->raise();
        viconCheckBox->raise();
        remoteIPlabel->raise();
        remoteIPLine->raise();
        droneNameLabel->raise();
        stop->raise();
        Ratelabel->raise();
        locPosLabel->raise();
        SysIDLabel->raise();
        sysIDLine->raise();
        compIDlabel->raise();
        compIDLine->raise();
        rateSlider->raise();

        retranslateUi(SenderWindow);

        QMetaObject::connectSlotsByName(SenderWindow);
    } // setupUi

    void retranslateUi(QWidget *SenderWindow)
    {
        SenderWindow->setWindowTitle(QApplication::translate("SenderWindow", "MavLink Sender", 0, QApplication::UnicodeUTF8));
        viconCheckBox->setText(QApplication::translate("SenderWindow", "VICON_POSITION_ESTIMATE", 0, QApplication::UnicodeUTF8));
        remoteIPlabel->setText(QApplication::translate("SenderWindow", "Remote IP: ", 0, QApplication::UnicodeUTF8));
        compIDlabel->setText(QApplication::translate("SenderWindow", "CompID: ", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("SenderWindow", "start", 0, QApplication::UnicodeUTF8));
        droneNameLabel->setText(QApplication::translate("SenderWindow", "DroneName", 0, QApplication::UnicodeUTF8));
        localPosCheckBox->setText(QApplication::translate("SenderWindow", "LOCAL_POSITION_NED", 0, QApplication::UnicodeUTF8));
        MotionCaptureLabel->setText(QApplication::translate("SenderWindow", "Motion Capture for: ", 0, QApplication::UnicodeUTF8));
        Ratelabel->setText(QApplication::translate("SenderWindow", "Rate", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("SenderWindow", "stop", 0, QApplication::UnicodeUTF8));
        remotePortLabel->setText(QApplication::translate("SenderWindow", "Remote Port:", 0, QApplication::UnicodeUTF8));
        SysIDLabel->setText(QApplication::translate("SenderWindow", "SystemID:", 0, QApplication::UnicodeUTF8));
        gpsCheckBox->setText(QApplication::translate("SenderWindow", "GPS_HIL", 0, QApplication::UnicodeUTF8));
        locPosLabel->setText(QApplication::translate("SenderWindow", "Local Position:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SenderWindow: public Ui_SenderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDERWINDOW_H
