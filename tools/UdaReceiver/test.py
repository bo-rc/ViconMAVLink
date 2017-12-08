from UdpReceiver import UdpReceiver

jeep = UdpReceiver(45454)

print('gps:')
for i in xrange(5):
    print(jeep.get_hil_gps())
    print('local NED:')
    print(jeep.get_loc_pos())

