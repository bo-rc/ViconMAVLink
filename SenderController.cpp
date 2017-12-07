/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    SenderController.cpp
 *
 * A Sender object reads Vicon data from a Station object, processes the data
 * with Kalman filtering and computes a GPS MAVLink data pack, sends MAVLink
 * messages to a robot via UDP.
 *
 * This is the Controller of the
 * Model(Sender)-View(SenderWindow)-Controller(SenderController) pattern.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#include "SenderController.h"

SenderController::SenderController(std::unique_ptr<Sender> &sender, QObject *parent) :
    QObject(parent),
    sender {sender}
{
    setupConnections();
    initialize();
}

QHostAddress SenderController::getRemoteAddress() const
{
    return sender->getRemoteAddress();
}

quint16 SenderController::getRemotePort() const
{
    return sender->getRemotePort();
}

uint8_t SenderController::getSysID() const
{
    return sender->getSysID();
}

uint8_t SenderController::getCompID() const
{
    return sender->getCompID();
}

bool SenderController::getUseGps() const
{
    return sender->getUseGps();
}

bool SenderController::getUseLocPos() const
{
    return sender->getUseLocPos();
}

bool SenderController::getUseVicon() const
{
    return sender->getUseVicon();
}

uint8_t SenderController::getRate() const
{
    return sender->getRate();
}

void SenderController::initialize()
{
    connect(sender.get(), &Sender::measUpdated,
	    this, &SenderController::updateMeasDisplay);
}

void SenderController::setupConnections()
{
    return;
}

void SenderController::startSender()
{
    sender->start();
}

void SenderController::stopSender()
{
    sender->stop();
}

void SenderController::setRate(uint8_t rate)
{
    sender->setRate(rate);
}

void SenderController::setUseGps(bool use)
{
    sender->setUseGps(use);
}

void SenderController::setUseVicon(bool use)
{
    sender->setUseVicon(use);
}

void SenderController::setUseLocPos(bool use)
{
    sender->setUseLocPos(use);
}

void SenderController::setSysID(uint8_t id)
{
    sender->setSysID(id);
}

void SenderController::setCompID(uint8_t id)
{
    sender->setCompID(id);
}

void SenderController::setRemoteAddress(const QString &ip)
{
    sender->setRemoteAddress(ip);
}

void SenderController::setRemotePort(quint16 port)
{
    sender->setRemotePort(port);
}

void SenderController::timerHandler()
{
    sender->timerHandler();
}

void SenderController::updateMeasDisplay()
{

}



