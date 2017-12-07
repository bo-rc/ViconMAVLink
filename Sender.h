/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    Sender.h
 *
 * A Sender object reads Vicon data from a Station object, processes the data
 * with Kalman filtering and computes a GPS MAVLink data pack, sends MAVLink
 * messages to a robot via UDP.
 *
 * This is the Model of the
 * Model(Sender)-View(SenderWindow)-Controller(SenderController) pattern.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QDateTime>
#include <lib/MAVLink2/common/mavlink.h>
#include <Station.h>
#include "KalmanFilter.h"
#include <memory>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(const QString& name, std::unique_ptr<Station>& station, QObject *parent = 0);
    ~Sender();
    void initialize();
    void setupConnections();

    void start();
    void stop();

    void updateMeas();
    void updateLocPosFromMeas();
    void updateGpsFromeLocPos();
    void sendDatagram();
    void startTimer(uint8_t rate);
    void stopTimer();
    void updateTimer(uint8_t rate);

    QHostAddress getRemoteAddress() const;
    quint16 getRemotePort() const;
    uint8_t getSysID() const;
    uint8_t getCompID() const;
    bool getUseGps() const;
    bool getUseLocPos() const;
    bool getUseVicon() const;
    uint8_t getRate() const;

    void setRate(uint8_t rate);
    void setUseGps(bool use);
    void setUseVicon(bool use);
    void setUseLocPos(bool use);
    void setSysID(uint8_t id);
    void setCompID(uint8_t id);
    void setRemoteAddress(const QString& ip);
    void setRemotePort(quint16 port);

signals:
    void measUpdated();

public slots:
    void timerHandler();

private:
    KalmanFilter kf;

    bool isInitialized;
    bool isRunning;

    std::unique_ptr<Station>& station;
    double dt; // seconds/frame
    long long frame;

    uint8_t rate;

    QTimer timer;

    bool useGPS;
    mavlink_hil_gps_t gpsMsg;

    bool useLocPos;
    mavlink_local_position_ned_t locPosMsg;

    bool useViconEst;
    mavlink_att_pos_mocap_t viconEstMsg;

    QString name;
    int sysid;
    int compid;

    QDateTime Qtime;

    qint64 ustime;

    QHostAddress remoteAddress;
    quint16 remotePort;
    QUdpSocket* udpSocket;

    //helpers
    mavlink_hil_gps_t locPos_to_gpsHIL(const mavlink_local_position_ned_t& locPos);
    void init_KF();
};

#endif // SENDER_H
