from UdpPass import *

vicon = UdpPass('/dev/ttyAMA0',45454)


print('Passing...')

vicon.passthrough()

