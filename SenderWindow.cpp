/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    SenderWindow.cpp
 *
 * A Sender object reads Vicon data from a Station object, processes the data
 * with Kalman filtering and computes a GPS MAVLink data pack, sends MAVLink
 * messages to a robot via UDP.
 *
 * This is the View of the
 * Model(Sender)-View(SenderWindow)-Controller(SenderController) pattern.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#include "SenderWindow.h"
#include "ui_SenderWindow.h"
#include <math.h>
#include <QMessageBox>

SenderWindow::SenderWindow(const QString& name, std::unique_ptr<SenderController> &controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SenderWindow),
    name(name),
    controller(controller)
{
    ui->setupUi(this);
    setupConnections();
    initialize();
}

void SenderWindow::initialize()
{
    setStandBy();
    ui->remoteIPLine->setText(controller->getRemoteAddress().toString());
    ui->remotePortLine->setText(QString::number(controller->getRemotePort()));
    ui->sysIDLine->setText(QString::number(controller->getSysID()));
    ui->compIDLine->setText(QString::number(controller->getCompID()));
    ui->gpsCheckBox->setChecked(controller->getUseGps());
    ui->localPosCheckBox->setChecked(controller->getUseLocPos());
    ui->viconCheckBox->setChecked(controller->getUseVicon());
    ui->rateSlider->setTickPosition(QSlider::TicksBothSides);
    ui->rateSlider->setMinimum(1);
    ui->rateSlider->setMaximum(240);
    ui->rateSlider->setSingleStep(1);
    ui->rateSlider->setValue(controller->getRate());

    auto r = ui->rateSlider->value();
    auto rate = 2 * floor(r/2);
    auto str = QString("Rate: ");
    str += QString::number(rate);
    str += QString(" Hz");
    ui->Ratelabel->setText(str);
}

void SenderWindow::setupConnections()
{
    connect(ui->rateSlider, &QSlider::sliderMoved,
	    this, &SenderWindow::updateRateLabel);
    connect(ui->start, &QPushButton::released,
	    this, &SenderWindow::startSenderHandler);
    connect(ui->stop, &QPushButton::released,
	    this, &SenderWindow::stopSenderHandler);
}

void SenderWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit closeSelf(name);
}

SenderWindow::~SenderWindow()
{
    delete ui;
}

void SenderWindow::setStandBy()
{
    auto str = name + QString("(stand by)");
    ui->droneNameLabel->setText(str);
    setLabelColor(ui->droneNameLabel, Qt::red);
}

void SenderWindow::setActive()
{
    auto str = name + QString("(active)");
    ui->droneNameLabel->setText(str);
    setLabelColor(ui->droneNameLabel, Qt::darkGreen);
}

void SenderWindow::updateRateLabel()
{
    auto r = ui->rateSlider->value();
    auto rate = 2 * floor(r/2);
    controller->setRate(rate);
    qDebug() << "updating Rate Label: " << rate;
    auto str = QString("Rate: ");
    str += QString::number(rate);
    str += QString(" Hz");
    ui->Ratelabel->setText(str);
}

void SenderWindow::startSenderHandler()
{
    if (!ui->remoteIPLine->isEnabled()) {
	QMessageBox msgBox;
	msgBox.setText("Sender is running!");
	msgBox.exec();
	return;
    }

    controller->setRemoteAddress(ui->remoteIPLine->text());
    controller->setRemotePort(ui->remotePortLine->text().toUShort());
    controller->setSysID(ui->sysIDLine->text().toInt());
    controller->setCompID(ui->compIDLine->text().toInt());
    controller->startSender();
    ui->remoteIPLine->setEnabled(false);
    ui->remotePortLine->setEnabled(false);
    ui->sysIDLine->setEnabled(false);
    ui->compIDLine->setEnabled(false);
    setActive();
}

void SenderWindow::stopSenderHandler()
{
    if (ui->remoteIPLine->isEnabled()) {
	QMessageBox msgBox;
	msgBox.setText("Sender is not running!");
	msgBox.exec();
	return;
    }
    controller->stopSender();
    ui->remoteIPLine->setEnabled(true);
    ui->remotePortLine->setEnabled(true);
    ui->sysIDLine->setEnabled(true);
    ui->compIDLine->setEnabled(true);
    setStandBy();
}

void SenderWindow::setLabelColor(QLabel * label, QColor color)
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::blue);
    palette.setColor(QPalette::WindowText, color);
    label->setPalette(palette);
}
