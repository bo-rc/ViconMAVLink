/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    Station.cpp
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
#include "Station.h"
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <sstream>
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <utility>
#include <set>
#include <algorithm>
#include <iterator>

using namespace ViconDataStreamSDK::CPP;

void Station::_connectVicon()
{
    shouldExit = false;

    if (vicon_.IsConnected().Connected) {
	QMessageBox msgBox;
	msgBox.setText("Vicon client is running.");
	msgBox.exec();
	return;
    }

    while( !vicon_.IsConnected().Connected && !shouldExit)
    {
	// Direct connection

	bool ok = false;
	QString host = hostAddress.toString();
	host += QString(":");
	host += QString::number(hostPort);
	std::cout << "connecting to ..." << host.toStdString() << std::endl;
	ok =( vicon_.Connect( host.toStdString() ).Result == Result::Success );

	if(!ok)
	{
	    std::cout << "Warning - connect failed..." << std::endl;
	}

	std::cout << ".";
#ifdef WIN32
	Sleep( 1000 );
#else
	sleep(1);
#endif
    }

    if (!vicon_.IsConnected().Connected)
    {
	std::cout << "connecting to Vicon failed." << std::endl;
	return;
    }

    vicon_.EnableSegmentData();
    vicon_.EnableMarkerData();

    vicon_.SetStreamMode(StreamMode::ServerPush);

    // MavLink uses NED coornidate frame, the following map assumes
    // Vicon is calibrated according to manual using the Wand with z up.
    if (north == "+x") {
	vicon_.SetAxisMapping(Direction::Forward,Direction::Right,Direction::Down);
    }
    else if (north == "-x") {
	vicon_.SetAxisMapping(Direction::Backward,Direction::Left,Direction::Down);
    }
    else if (north == "+y") {
	vicon_.SetAxisMapping(Direction::Left,Direction::Forward,Direction::Down);
    }
    else if (north == "-y") {
	vicon_.SetAxisMapping(Direction::Right,Direction::Backward,Direction::Down);
    }

    std::cout << "North mapped to " << north.toStdString() << std::endl;

    auto _Output_GetAxisMapping = vicon_.GetAxisMapping();
    qDebug() << "Axis Mapping: X-" << _Adapt( _Output_GetAxisMapping.XAxis )
	      << " Y-" << _Adapt( _Output_GetAxisMapping.YAxis )
	      << " Z-" << _Adapt( _Output_GetAxisMapping.ZAxis );
    vicon_.GetFrame();
    auto frame_rate = vicon_.GetFrameRate();
    rate = frame_rate.FrameRateHz;
    std::cout << "frame rate = " << frame_rate.FrameRateHz << std::endl;
    std::cout << "Vicon origin GPS: " << originGPS.lat << "," << originGPS.lon << "," << originGPS.alt << std::endl;
    setdt(1.0/rate); // initial value for dt (second/frame)

    emit ViconConnected();
}

void Station::setupConnections()
{
    connect(this, &Station::ViconConnected,
	    this, &Station::dataStream);
}


Station::Station(QObject *parent) : QObject(parent),
    vicon_(ViconDataStreamSDK::CPP::Client())
{
    initialize();
    setupConnections();
}

void Station::initialize()
{
    isInitialized = false;
    shouldExit = false;

    /* the following values will appear in UI */
    hostAddress = QHostAddress("192.168.1.3");
    hostPort = 801;
    originGPS.lat = 40.1156786;
    originGPS.lon = -88.2243507;
    originGPS.alt = 222.196;
    originGPS.gps_to_local = GeographicLib::LocalCartesian(originGPS.lat,
							   originGPS.lon,
							   originGPS.alt);
    north = "+x";
}

Station::~Station()
{
    disconnectVicon();
}

QHostAddress Station::getHostAddress() const
{
    return hostAddress;
}

void Station::setHostAddress(const QHostAddress &value)
{
    hostAddress = value;
}

quint16 Station::getHostPort() const
{
    return hostPort;
}

void Station::setHostPort(const quint16 &value)
{
    hostPort = value;
}

double Station::getRate() const
{
    return rate;
}

void Station::setRate(double value)
{
    rate = value;
}

void Station::connectVicon()
{
    isInitialized = false;
    viconConnectFuture = QtConcurrent::run(this, &Station::_connectVicon);
}

void Station::disconnectVicon()
{
    shouldExit = true;

    dataStreamFuture.cancel();
    viconConnectFuture.cancel();
    dataStreamFuture.waitForFinished();
    viconConnectFuture.waitForFinished();

    if (!vicon_.IsConnected().Connected) {
        QMessageBox msgBox;
	msgBox.setText("Vicon client is NOT connected.");
        msgBox.exec();
        return;
    }

    vicon_.DisableMarkerData();
    vicon_.DisableSegmentData();

    std::cout << " Disconnecting Vicon..." << std::endl;
    vicon_.Disconnect();
    std::cout << " Disconnected! " << std::endl;

    emit ViconDisconnected();
}

void Station::addDrone(const QString &name)
{
    if (droneCollection.contains(name)) {
	std::cout << "Drone: " << name.toStdString() << " already exists." << std::endl;
        return;
    }

    droneCollection.insert(name, Drone(name));
    emit droneAdded(name);
}

void Station::addDrone(const QString &name, double x, double y, double z, double q_0, double q_1, double q_2, double q_3)
{
    if (droneCollection.contains(name)) {
	std::cout << "Drone: " << name.toStdString() << " already exists." << std::endl;
        return;
    }

    droneCollection.insert(name, Drone(name, x, y, z, q_0, q_1, q_2, q_3));
    emit droneAdded(name);
}

void Station::removeDrone(const QString &name)
{
    if (droneCollection.contains(name)) {
	droneCollection.remove(name);
	emit droneRemoved(name);
    }
}

void Station::_dataStream()
{
    int counter = 0;
    while (!shouldExit) {
	if (counter > 1000) {
	    qDebug() << "Streaming ... ";
	    counter = 0;
	} else {
	    ++counter;
	}

	while( vicon_.GetFrame().Result != Result::Success )
	{
	    // Sleep a little so that we don't lumber the CPU with a busy poll
#ifdef WIN32
	    Sleep( 200 );
#else
	    sleep(1);
#endif
	}

	Output_GetFrameNumber _Output_GetFrameNumber = vicon_.GetFrameNumber();

	// update drone collection
	auto subCount = vicon_.GetSubjectCount().SubjectCount;
	std::set<QString> activeDroneNames;
	for (uint i = 0; i != subCount; ++i) {
	    auto subName = QString::fromStdString(std::string(vicon_.GetSubjectName(i).SubjectName));
	    activeDroneNames.insert(subName);

	    if (!droneCollection.contains(subName)) {
		addDrone(subName);
	    }
	}

	std::vector<QString> inactiveDroneNames;
	for (const auto& x : droneCollection) {
	    if (activeDroneNames.count(x.getName()) == 0)
		inactiveDroneNames.push_back(x.getName());
	}

	for (const auto& x : inactiveDroneNames)
	    removeDrone(x);

	auto frameNew = _Output_GetFrameNumber.FrameNumber; // use frame number as a hardware time

	if (!isInitialized) { // do not update dt in initialization
	    setFrame(frameNew);
	    for (auto& x : droneCollection) {
		auto drone_translation = vicon_.GetSegmentLocalTranslation(x.getName().toStdString(), x.getName().toStdString());
		auto drone_rotation = vicon_.GetSegmentLocalRotationQuaternion(x.getName().toStdString(), x.getName().toStdString());

		mavlink_att_pos_mocap_t pos;
		// ---- writing data start ---- //
		lock.lockForWrite();
		pos.x = drone_translation.Translation[0] / 1000.0;
		pos.y = drone_translation.Translation[1] / 1000.0;
		pos.z = drone_translation.Translation[2] / 1000.0;

		pos.q[0] = drone_rotation.Rotation[0];
		pos.q[1] = drone_rotation.Rotation[1];
		pos.q[2] = drone_rotation.Rotation[2];
		pos.q[3] = drone_rotation.Rotation[3];

		x.setPos(pos);
		x.setTime(frameNew);
		lock.unlock();
		// ---- writing data end ---- //
	    }
	    isInitialized = true;
	}

	auto frameDiff = frameNew - getFrame();
	setFrame(frameNew);
	setdt(frameDiff/rate);
	emit dtUpdated(dt);

//	if ( frameDiff > 1 )
//	    qDebug() << frameDiff-1 << " frames dropped, transient dt = " << dt*1000 << " ms";

	for (auto& x : droneCollection) {
	    auto drone_translation = vicon_.GetSegmentLocalTranslation(x.getName().toStdString(), x.getName().toStdString());
	    auto drone_rotation = vicon_.GetSegmentLocalRotationQuaternion(x.getName().toStdString(), x.getName().toStdString());

	    mavlink_att_pos_mocap_t pos;
	    // ---- writing data start ---- //
	    lock.lockForWrite();
	    pos.x = drone_translation.Translation[0];
	    pos.y = drone_translation.Translation[1];
	    pos.z = drone_translation.Translation[2];

	    pos.q[0] = drone_rotation.Rotation[0];
	    pos.q[1] = drone_rotation.Rotation[1];
	    pos.q[2] = drone_rotation.Rotation[2];
	    pos.q[3] = drone_rotation.Rotation[3];

	    x.setPos(pos);
	    x.setTime(frameNew);
	    lock.unlock();
	    // ---- writing data end ---- //
	}
    }
}

void Station::dataStream()
{
    dataStreamFuture = QtConcurrent::run(this, &Station::_dataStream);
}

double Station::getdt() const
{
    return dt;
}

void Station::setdt(double value)
{
    dt = value;
}

long long Station::getFrame() const
{
    return frame;
}

void Station::setFrame(long long value)
{
    frame = value;
}

mavlink_att_pos_mocap_t Station::getMeas(const QString& name, long long &frame)
{
    lock.lockForRead();
    auto ret = droneCollection[name].getPos(frame);
    lock.unlock();
    return ret;
}

QString Station::getOriginGPS() const
{
    std::string gps = std::to_string(originGPS.lat);
    gps = gps + ',';
    gps = gps + std::to_string(originGPS.lon);
    gps = gps + ',';
    gps = gps + std::to_string(originGPS.alt);

    return QString::fromStdString(gps);
}

void Station::setOriginGPS(const QString &q_gps)
{
    std::istringstream stream(q_gps.toStdString());
    std::vector<double> entries;
    std::string entry;
    while(getline(stream, entry, ',')) {
	entries.push_back(std::atof(entry.c_str()));
    }

    originGPS.gps_to_local = GeographicLib::LocalCartesian(entries[0],entries[1],entries[2]);
    originGPS.lat = entries[0];
    originGPS.lon = entries[1];
    originGPS.alt = entries[2];

}

GeographicLib::LocalCartesian Station::getGpsToLocal() const
{
    return originGPS.gps_to_local;
}

void Station::setNorth(const QString &axis)
{
    north = axis;
}

QString Station::_Adapt( const Direction::Enum i_Direction )
{
  switch( i_Direction )
  {
    case Direction::Forward:
      return QString("Forward");
    case Direction::Backward:
      return QString("Backward");
    case Direction::Left:
      return QString("Left");
    case Direction::Right:
      return QString("Right");
    case Direction::Up:
      return QString("Up");
    case Direction::Down:
      return QString("Down");
    default:
      return QString("Unknown");
  }
}
