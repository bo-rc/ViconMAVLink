import socket, serial

from pymavlink import mavutil


class UdpPass:

    consumed_ports = []

    @staticmethod
    def get_ip_address():
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]

    '''a UDP connection to receive data'''
    def __init__(self, fc_device, local_port):
        self._port = str(local_port)
        if self._port in UdpPass.consumed_ports:
            raise Exception('port already used!')

        UdpPass.consumed_ports.append(self._port)
        self._ip = UdpPass.get_ip_address()
        self._connection_string = 'udp:' + self._ip + ':' + self._port
        self._mavudp = mavutil.mavlink_connection(self._connection_string)

        # Create serial device
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


    # Wait for Mavlink messages and send them on when they are received
    def passthrough(self):
        while(True) :
            msg = None
            while msg is None:
                msg = self._mavudp.recv_msg()
            self._mavserial.write(msg.get_msgbuf())



