/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    Drone.h
 *
 * A Drone object stores raw measurements fetched from Vicon.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */

#ifndef DRONE_H
#define DRONE_H

#include <QString>
#include <lib/MAVLink2/common/mavlink.h>

class Drone
{
public:
    Drone();
    virtual ~Drone();
    Drone(QString droneName, double x, double y, double z, double q_0, double q_1, double q_2, double q_3);
    Drone(QString droneName);
    QString getName() const;
    void setName(const QString &value);

    mavlink_att_pos_mocap_t getPos() const;
    mavlink_att_pos_mocap_t getPos(long long& ret_frame) const;
    void setPos(const mavlink_att_pos_mocap_t &value);

    void reset();

    long long getTime() const;
    void setTime(long long value);

private:
    QString name;
    mavlink_att_pos_mocap_t pos;
    long long frame;
};

#endif // DRONE_H
