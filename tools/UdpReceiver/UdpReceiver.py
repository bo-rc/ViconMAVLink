import socket

from pymavlink import mavutil


class UdpReceiver:

    consumed_ports = []

    @staticmethod
    def get_ip_address():
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]

    '''a UDP connection to receive data'''
    def __init__(self, local_port):
        self._port = str(local_port)
        if self._port in UdpReceiver.consumed_ports:
            raise Exception('port already used!')

        UdpReceiver.consumed_ports.append(self._port)
        self._ip = UdpReceiver.get_ip_address()
        self._connection_string = 'udp:' + self._ip + ':' + self._port
        self._mavudp = mavutil.mavlink_connection(self._connection_string)
        self._data = {}

    def get_port(self):
        return self._port

    def get_ip(self):
        return self._ip

    def update_data(self, msg_type_list):
        for msg_type_string in msg_type_list:
            msg = None
            while msg is None:
                msg = self._mavudp.recv_match(type=msg_type_string)
            self._data[msg_type_string] = msg

    def get_loc_pos(self):
        self.update_data(['LOCAL_POSITION_NED'])
        return self._data['LOCAL_POSITION_NED']

    def get_hil_gps(self):
        self.update_data(['HIL_GPS'])
        return self._data['HIL_GPS']

    def get_atti(self):
        self.update_data('ATTITUDE')
        return self._data['ATTITUDE']

    def get_mocap(self):
        self.update_data('ATT_POS_MOCAP')
        return self._data['ATT_POS_MOCAP']



