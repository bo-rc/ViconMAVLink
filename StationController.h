/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    StationController.h
 *
 * A Station object organizes drones and senders, communicates with Vicon and
 * updates measurements for drones using a separate thread.
 *
 * A StationWindow is the main GUI.
 *
 * This is the Controller of the
 * Model(Station)-View(StationWindow)-Controller(StationController) pattern.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#ifndef STATIONCONTROLLER_H
#define STATIONCONTROLLER_H

#include <QObject>
#include <Station.h>
#include <memory>
#include <vector>
#include <QTimer>

class StationController : public QObject
{
    Q_OBJECT
public:
    explicit StationController(std::unique_ptr<Station>& station, QObject *parent = 0);
    void connectVicon();
    void disconnectVicon();

    QHostAddress getHostAddress();
    quint16 getHostPort();
    std::vector<QString> getTrackingObjectNames();
    QString getOriginGPS();
    double getFrameRate();
    double getdt();
    std::unique_ptr<Station> &getStation();

    void setHostAddress(QString ip);
    void setHostPort(quint16 hport);
    void setOriginGPS(const QString &q_gps);
    void setNorth(const QString& axis);

signals:
    void droneNameAdded(QString name);
    void droneNameRemoved(QString name);
    void viconConnected();
    void viconDisconnected();
    void dtUpdated(double dt);

public slots:
    void addDrone(QString name);
    void removeDrone(QString name);
    void viconConnectedHandler();
    void viconDisconnectedHandler();
    void dtUpdatedHandler();

private:
    std::unique_ptr<Station>& station;
    void initialize();
    void setupConnections();
    QTimer dtUpdateTimer;
};

#endif // STATIONCONTROLLER_H
