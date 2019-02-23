/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    SenderController.h
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
#ifndef SENDERCONTROLLER_H
#define SENDERCONTROLLER_H

#include <memory>
#include <QObject>
#include <QTimer>
#include "Sender.h"

class SenderController : public QObject
{
    Q_OBJECT
  public:
    explicit SenderController(std::unique_ptr<Sender> &sender, QObject *parent = 0);

  signals:

  public slots:
    QHostAddress getRemoteAddress() const;
    quint16 getRemotePort() const;
    uint8_t getSysID() const;
    uint8_t getCompID() const;
    bool getUseGps() const;
    bool getUseLocPos() const;
    bool getUseVicon() const;
    uint8_t getRate() const;

    void startSender();
    void stopSender();
    void setRate(uint8_t rate);
    void setUseGps(bool use);
    void setUseVicon(bool use);
    void setUseLocPos(bool use);
    void setSysID(uint8_t id);
    void setCompID(uint8_t id);
    void setRemoteAddress(const QString &ip);
    void setRemotePort(quint16 port);
    void timerHandler();
    void updateMeasDisplay();

  private:
    std::unique_ptr<Sender> &sender;
    void initialize();
    void setupConnections();
    QTimer timer;
};

#endif // SENDERCONTROLLER_H
