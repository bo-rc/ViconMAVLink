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
#include "StationController.h"

StationController::StationController(std::unique_ptr<Station> &station, QObject *parent) : QObject(parent),
                                                                                           station(station)
{
    setupConnections();
    initialize();
}

void StationController::setupConnections()
{
    connect(station.get(), &Station::droneAdded,
            this, &StationController::addDrone);
    connect(station.get(), &Station::droneRemoved,
            this, &StationController::removeDrone);
    connect(station.get(), &Station::dtUpdated,
            this, &StationController::dtUpdatedHandler);
    connect(station.get(), &Station::ViconConnected,
            this, &StationController::viconConnectedHandler);
    connect(station.get(), &Station::ViconDisconnected,
            this, &StationController::viconDisconnectedHandler);
    connect(&dtUpdateTimer, SIGNAL(timeout()), this, SLOT(dtUpdatedHandler()));
}

void StationController::initialize()
{
    dtUpdateTimer.start(500);
}

void StationController::connectVicon()
{
    station->connectVicon();
}

void StationController::disconnectVicon()
{
    station->disconnectVicon();
}

QHostAddress StationController::getHostAddress()
{
    return station->getHostAddress();
}

void StationController::setHostAddress(QString ip)
{
    station->setHostAddress(QHostAddress(ip));
}

quint16 StationController::getHostPort()
{
    return station->getHostPort();
}

void StationController::setHostPort(quint16 hport)
{
    station->setHostPort(hport);
}

std::vector<QString> StationController::getTrackingObjectNames()
{
    std::vector<QString> names;
    for (const auto &x : station->droneCollection)
    {
        names.push_back(x.getName());
    }

    return names;
}

QString StationController::getOriginGPS()
{
    return station->getOriginGPS();
}

void StationController::setOriginGPS(const QString &q_gps)
{
    station->setOriginGPS(q_gps);
}

void StationController::setNorth(const QString &axis)
{
    station->setNorth(axis);
}

double StationController::getFrameRate()
{
    return station->getRate();
}

double StationController::getdt()
{
    return station->getdt();
}

std::unique_ptr<Station> &StationController::getStation()
{
    return station;
}

void StationController::addDrone(QString name)
{
    emit droneNameAdded(name);
}

void StationController::removeDrone(QString name)
{
    emit droneNameRemoved(name);
}

void StationController::viconConnectedHandler()
{
    emit viconConnected();
}

void StationController::viconDisconnectedHandler()
{
    emit viconDisconnected();
}

void StationController::dtUpdatedHandler()
{
    auto dt = station->getdt();
    emit dtUpdated(dt);
}
