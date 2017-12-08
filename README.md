# ViconMAVLink
ViconMAVLink is an application to provide indoor positioning for networked robots using Vicon motion capture measurements. It is primarily used in the [Intellegent Robotics Lab](robotics.illinois.edu) at the University of Illinois as a tool to simulate indoor GPS for Linux-based autonomous vehicles.

# Dependencies
ViconMAVLink uses the following libraries:
* [Vicon DataStream SDK](https://www.vicon.com/products/software/datastream-sdk): to obtain real-time, high-precision positioning measurement for objects.
* [MAVLink library](http://qgroundcontrol.org/mavlink/start): to encode/unpack UDP data with the MAVLink protocol.
* [GeographicLib](https://geographiclib.sourceforge.io/): to convert positioning data between local coordinates and GPS locations.
* [QT5](https://www.qt.io/) (core gui widgets network concurrent, also qwt): to provide a GUI, networking and multithreading.

As long as you have all required libraries added to the Qt project file. This application can be built for multiple platforms in [QtCreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/).

# User's Guide
You can run this app directly on the Vicon server computer or on any other computers as long as they are in the same network as the Vicon server computer. After you launch the application, the main window appears. 

![main_window_start](figs/main_window_start.jpg)

The capture objects list is empty because you haven't connected to Vicon yet. 

* The `HostAddress` is the IP address of the Vicon server computer. 
* The `HostPort` usually is `801`. This is the port used by Vicon.
* The `North` mapping: Vicon uses a _Forward-Left-Up_ coornidates while the `LOCAL_POSITION_NED` message in MAVLink uses _North-East-Down_, to make the situation more confusing, GeographicLib uses a _East-North-Up_ coordinates. To convert position data correctly, you need to map your Vicon axis first. Assuming you calibrated Vicon according to the manual, just choose the correct half-axis that corresponds to North then this app will handle the mapping correctly.

__To connect to Vicon__: Click `Menu`->`Connect Vicon` then objects that are captured by Vicon will appear in the Captured Objects List.

![main_window_connect](figs/main_window_connect.gif)

__To launch a sender for a robot__: Choose an object then Click `Start a MavLink Sender`. A Sender window will appear as the following:
![sender_window_start](figs/main_window_start.jpg)

__To stream positioning data to the robot__: 
![sender_window_connect](figs/sender_window_connect.gif)

You may launch multiple senders for a fleet of robots.

# Developer's Guide
The Station object will launch a separate thread to communicate with Vicon. A Writer/Reader lock is used to synchronize data. The Station object is the writer and Sender objects are the readers who fetch raw data, a position (mm) and a quarternion encapsulated in a `mavlink_att_pos_mocap_t` object from the station. Since Vicon does not output velocities of objects, the Sender uses a linear Kalman filter to compute a `mavlink_local_position_ned_t` object with positions and velocities. The `GPS_HIL` data is then computed with the local position object. 




