/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    Sender.cpp
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
#include "Sender.h"
#include <cmath>
#include <chrono>
using Eigen::MatrixXd;
using Eigen::VectorXd;

Sender::Sender(const QString &name, std::unique_ptr<Station> &station, QObject *parent) : QObject(parent),
                                                                                          isInitialized{false},
                                                                                          isRunning{false},
                                                                                          station{station},
                                                                                          name{name},
                                                                                          udpSocket{new QUdpSocket(this)}
{
    initialize();
    setupConnections();
}

Sender::~Sender()
{
    delete udpSocket;
    qDebug() << "Sender destructor.";
}

void Sender::setupConnections()
{
    connect(&timer, SIGNAL(timeout()),
            this, SLOT(timerHandler()));
}

void Sender::start()
{
    startTimer(rate);
}

void Sender::stop()
{
    stopTimer();
}

void Sender::initialize()
{
    // init x, dt
    updateMeas();

    // init Kalmen Filter using newly-fetched x, dt
    init_KF();

    /* the following will appear on UI */
    rate = 10;
    useGPS = true;
    useLocPos = true;
    useViconEst = true;
    sysid = 1;
    compid = 1;
    remoteAddress = QHostAddress("192.168.1.2");
    remotePort = 45454;
}

void Sender::init_KF()
{
    VectorXd x_in(6);
    x_in << viconEstMsg.x / 1000.0, viconEstMsg.y / 1000.0, viconEstMsg.z / 1000.0,
        0.0, 0.0, 0.0;

    MatrixXd P_in(6, 6);
    P_in << 0.1, 0, 0, 0, 0, 0,
        0, 0.1, 0, 0, 0, 0,
        0, 0, 0.1, 0, 0, 0,
        0, 0, 0, 10., 0, 0,
        0, 0, 0, 0, 10., 0,
        0, 0, 0, 0, 0, 10.;

    MatrixXd F_in(6, 6);
    F_in << 1, 0, 0, dt, 0, 0,
        0, 1, 0, 0, dt, 0,
        0, 0, 1, 0, 0, dt,
        0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 1;

    MatrixXd Q_in(6, 6);
    Q_in << 1, 0, 0, 1, 0, 0,
        0, 1, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 0, 0,
        0, 1, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 1;

    MatrixXd H_in(3, 6);
    H_in << 1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0;

    MatrixXd R_in(3, 3);
    R_in << 0.01, 0, 0,
        0, 0.01, 0,
        0, 0, 0.01;

    kf.init(x_in, P_in, F_in, Q_in, H_in, R_in);
}

void Sender::updateTimer(uint8_t r)
{
    rate = r;
    if (isRunning)
    {
        stopTimer();
        startTimer(rate);
    }
}

void Sender::startTimer(uint8_t rate)
{
    auto msecTime = 1.0 / rate * 1000;
    timer.start(msecTime);
    isRunning = true;
}

void Sender::stopTimer()
{
    timer.stop();
    isRunning = false;
}

QHostAddress Sender::getRemoteAddress() const
{
    return remoteAddress;
}

quint16 Sender::getRemotePort() const
{
    return remotePort;
}

uint8_t Sender::getSysID() const
{
    return sysid;
}

uint8_t Sender::getCompID() const
{
    return compid;
}

bool Sender::getUseGps() const
{
    return useGPS;
}

bool Sender::getUseLocPos() const
{
    return useLocPos;
}

bool Sender::getUseVicon() const
{
    return useViconEst;
}

uint8_t Sender::getRate() const
{
    return rate;
}

void Sender::setRate(uint8_t rate)
{
    this->rate = rate;
    updateTimer(rate);
}

void Sender::setUseGps(bool use)
{
    useGPS = use;
}

void Sender::setUseVicon(bool use)
{
    useViconEst = use;
}

void Sender::setUseLocPos(bool use)
{
    useLocPos = use;
}

void Sender::setSysID(uint8_t id)
{
    sysid = id;
}

void Sender::setCompID(uint8_t id)
{
    compid = id;
}

void Sender::timerHandler()
{
    updateMeas();
    updateLocPosFromMeas();
    updateGpsFromeLocPos();
    sendDatagram();
    emit measUpdated();
}

void Sender::setRemoteAddress(const QString &value)
{
    remoteAddress = QHostAddress(value);
}

void Sender::setRemotePort(quint16 port)
{
    remotePort = port;
}

void Sender::updateMeas()
{
    auto now = std::chrono::system_clock::now();
    auto microsec = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto epoch = microsec.time_since_epoch();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
    ustime = duration.count();

    qDebug() << "ustime: " << ustime;

    if (!isInitialized)
    {
        viconEstMsg = station->getMeas(name, frame);
        dt = 1.0 / rate;
        isInitialized = true;
        return;
    }

    // update frame number and measurement
    auto prev_frame = frame;
    viconEstMsg = station->getMeas(name, frame);

    // update dt
    if (frame > prev_frame)
    {
        dt = (frame - prev_frame) / station->getRate();
    }
    else
    {
        dt = 1.0 / rate;
    }

    qDebug() << "updating Vicon, time: " << ustime << " dt = " << dt;
    qDebug() << "Vicon pos:" << viconEstMsg.x << "," << viconEstMsg.y << "," << viconEstMsg.z;
}

/* call this function after calling updateMeas() */
void Sender::updateLocPosFromMeas()
{
    kf.update_dt(dt);

    kf.predict();
    VectorXd z(3);
    z << viconEstMsg.x / 1000.0,
        viconEstMsg.y / 1000.0,
        viconEstMsg.z / 1000.0; // unit is meter
    kf.update(z);
    locPosMsg.x = kf.x_[0];
    locPosMsg.y = kf.x_[1];
    locPosMsg.z = kf.x_[2];
    locPosMsg.vx = kf.x_[3];
    locPosMsg.vy = kf.x_[4];
    locPosMsg.vz = kf.x_[5];

    qDebug() << "updateing locPos";
    qDebug() << "locPos state vector: " << locPosMsg.x << ","
             << locPosMsg.y << ","
             << locPosMsg.z << ","
             << locPosMsg.vx << ","
             << locPosMsg.vy << ","
             << locPosMsg.vz;
}

/* call this function after calling updateLocPosFromMeas() */
void Sender::updateGpsFromeLocPos()
{
    GeographicLib::LocalCartesian geoLocal = station->getGpsToLocal();

    double lat, lon, alt;
    /* geographiclib uses east-north-up coordination */
    geoLocal.Reverse(locPosMsg.y, locPosMsg.x, -locPosMsg.z, lat, lon, alt);
    double groundSpeed = sqrt(pow(locPosMsg.vx, 2) + pow(locPosMsg.vy, 2));
    double courseOverGround = atan(locPosMsg.vy / locPosMsg.vx) * 180 / M_PI;

    gpsMsg.time_usec = ustime;           // in microsecond
    gpsMsg.lat = lat * 10000000;         // [degrees * 1E7]
    gpsMsg.lon = lon * 10000000;         // [degrees * 1E7]
    gpsMsg.alt = alt * 1000;             // [m * 1000] AMSL
    gpsMsg.vel = groundSpeed * 100;      // [cm/s]
    gpsMsg.vn = locPosMsg.vx * 100;      // [cm/s]
    gpsMsg.ve = locPosMsg.vy * 100;      // [cm/s]
    gpsMsg.vd = locPosMsg.vz * 100;      // [cm/s]
    gpsMsg.cog = courseOverGround * 100; // [degrees * 100]
    gpsMsg.eph = 0.01;                   // <1: ideal
    gpsMsg.epv = 0.01;                   // <1: ideal
    gpsMsg.fix_type = 3;
    gpsMsg.satellites_visible = 10;

    qDebug() << "updating GPS";
    qDebug() << "GPS time: " << gpsMsg.time_usec;
    qDebug() << "GPS coord: " << gpsMsg.lat << "," << gpsMsg.lon << ", " << gpsMsg.alt;
    qDebug() << "GPS velocity: " << gpsMsg.vn << ", " << gpsMsg.ve << ", " << gpsMsg.vd;
}

void Sender::sendDatagram()
{
    uint8_t len = 0;
    constexpr int BUFSIZE = 512;

    if (useLocPos)
    {
        qDebug() << "sending locPos";
        mavlink_message_t msg_loc;
        uint8_t send_buf_loc[BUFSIZE];
        memset(send_buf_loc, 0, BUFSIZE);

        mavlink_msg_local_position_ned_encode(sysid, compid, &msg_loc, &locPosMsg);
        len = mavlink_msg_to_send_buffer(send_buf_loc, &msg_loc);
        qDebug() << "sending to " << remoteAddress << "," << remotePort;
        udpSocket->writeDatagram(reinterpret_cast<const char *>(send_buf_loc), len, remoteAddress, remotePort);
    }

    if (useGPS)
    {
        qDebug() << "sending GPS";
        mavlink_message_t msg_gps;
        uint8_t send_buf_gps[BUFSIZE];
        memset(send_buf_gps, 0, BUFSIZE);

        mavlink_msg_hil_gps_encode(sysid, compid, &msg_gps, &gpsMsg);
        len = mavlink_msg_to_send_buffer(send_buf_gps, &msg_gps);
        udpSocket->writeDatagram(reinterpret_cast<const char *>(send_buf_gps), len, remoteAddress, remotePort);
    }

    if (useViconEst)
    {
        qDebug() << "sending Vicon";
        mavlink_message_t msg_mocap;
        uint8_t send_buf_mocap[BUFSIZE];
        memset(send_buf_mocap, 0, BUFSIZE);

        mavlink_msg_att_pos_mocap_encode(sysid, compid, &msg_mocap, &viconEstMsg);
        len = mavlink_msg_to_send_buffer(send_buf_mocap, &msg_mocap);
        udpSocket->writeDatagram(reinterpret_cast<const char *>(send_buf_mocap), len, remoteAddress, remotePort);
    }
}
