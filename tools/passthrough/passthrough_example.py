from UdpReceiver import *

vicon = UdpReceiver('/dev/ttyAMA0',45454)


print('running...')
while(True) :
	vicon.passthrough()

