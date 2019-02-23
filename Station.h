/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    Station.h
 *
 * A Station object organizes drones and senders, communicates with Vicon and
 * updates measurements for drones using a separate thread.
 *
 * A StationWindow is the main GUI.
 *
 * This is the Model of the
 * Model(Station)-View(StationWindow)-Controller(StationController) pattern.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QMap>
#include <QList>
#include <QReadWriteLock>
#include <QtConcurrent/QtConcurrent>
#include <GeographicLib/LocalCartesian.hpp>
#include "DataStreamClient.h"
#include "Drone.h"

class Station : public QObject
{
    Q_OBJECT
  public:
    explicit Station(QObject *parent = 0);
    virtual ~Station();

    QHostAddress getHostAddress() const;
    void setHostAddress(const QHostAddress &value);

    quint16 getHostPort() const;
    void setHostPort(const quint16 &value);

    double getRate() const;
    void setRate(double value);

    void connectVicon();
    void disconnectVicon();

    void addDrone(const QString &name, double x, double y, double z,
                  double q_0, double q_1, double q_2, double q_3);

    void addDrone(const QString &name);
    mavlink_vicon_position_estimate_t getViconMeas(const QString &name);

    void removeDrone(const QString &name);

    void dataStream();

    QMap<QString, Drone> droneCollection;
    QReadWriteLock lock;

    QString getOriginGPS() const;
    void setOriginGPS(const QString &q_gps);

    GeographicLib::LocalCartesian getGpsToLocal() const;

    void setNorth(const QString &axis);

    double getdt() const;
    void setdt(double value);

    long long getFrame() const;
    void setFrame(long long value);

    mavlink_att_pos_mocap_t getMeas(const QString &name, long long &frame);

  signals:
    void ViconConnected();
    void ViconDisconnected();
    void droneAdded(QString name);
    void droneRemoved(QString name);
    void dtUpdated(double dt);

  public slots:

  private:
    double dt; // seconds/frame
    long long frame;
    double rate;
    int vicon_x_mapping;
    int vicon_y_mapping;
    int vicon_z_mapping;

    ViconDataStreamSDK::CPP::Client vicon_;
    bool shouldExit;
    bool isInitialized;

    QHostAddress hostAddress;
    quint16 hostPort;
    struct originGPS
    {
        double lat;
        double lon;
        double alt;
        GeographicLib::LocalCartesian gps_to_local;
    } originGPS;

    QString north;

    QFuture<void> dataStreamFuture;
    QFuture<void> viconConnectFuture;
    void _connectVicon();
    void _dataStream();
    void setupConnections();
    void initialize();

    // helpers
    QString _Adapt(const ViconDataStreamSDK::CPP::Direction::Enum i_Direction);
};

#endif // STATION_H
