/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    Drone.cpp
 *
 * A Drone object stores raw measurements fetched from Vicon.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#include "Drone.h"

Drone::Drone()
{

}

Drone::Drone(QString droneName)
{
    name = droneName;
}

Drone::~Drone()
{
    // nothing to do
}

Drone::Drone(QString droneName, double x, double y, double z, double q_0, double q_1, double q_2, double q_3)
{
    name = droneName;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    pos.q[0] = q_0;
    pos.q[1] = q_1;
    pos.q[2] = q_2;
    pos.q[3] = q_3;
}

QString Drone::getName() const
{
    return name;
}

void Drone::setName(const QString &value)
{
    name = value;
}

mavlink_att_pos_mocap_t Drone::getPos(long long& ret_frame) const
{
    ret_frame = frame;
    return pos;
}

mavlink_att_pos_mocap_t Drone::getPos() const
{
    return pos;
}

void Drone::setPos(const mavlink_att_pos_mocap_t &value)
{
    pos = value;
}

void Drone::reset()
{
    name = "";
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    pos.q[0] = 1;
    pos.q[1] = 1;
    pos.q[2] = 1;
    pos.q[3] = 1;
    frame = 0;
}

long long Drone::getTime() const
{
    return frame;
}

void Drone::setTime(long long value)
{
    frame = value;
}
