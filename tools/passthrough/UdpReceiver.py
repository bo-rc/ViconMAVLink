import socket, serial

from pymavlink import mavutil


class UdpReceiver:

    consumed_ports = []

    @staticmethod
    def get_ip_address():
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]

    '''a UDP connection to receive data'''
    def __init__(self, fc_device, local_port):
        self._port = str(local_port)
        if self._port in UdpReceiver.consumed_ports:
            raise Exception('port already used!')

        UdpReceiver.consumed_ports.append(self._port)
        self._ip = UdpReceiver.get_ip_address()
        self._connection_string = 'udp:' + self._ip + ':' + self._port
        self._mavudp = mavutil.mavlink_connection(self._connection_string)
        try:
            self._mavserial = mavutil.mavlink_connection(fc_device,baud=921600)
        except serial.serialutil.SerialException : 
            print("\n\tSerial device " + fc_device +" not available\n")
            exit(1)


        self._data = {}
        print(self._connection_string)
        #print(self._mavserial.baud)

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
            self._mavserial.write(msg)

    def passthrough(self):
        msg = None
        while msg is None:
            msg = self._mavudp.recv_msg()
	#print(msg)
        self._mavserial.write(msg.get_msgbuf())



