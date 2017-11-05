from pymavlink import mavutil
import sys
from threading import Thread
import time
from time import sleep
import datetime
import struct

mav = mavutil.mavlink_connection('/dev/ttySAC0', baud=57600)
unix_time = int(time.time())
print(datetime.datetime.fromtimestamp(unix_time))
time_unix_usec = unix_time * 1000000 # sec to usec
time_boot_ms = 0
time_boot_ms = 0x0808
x=struct.unpack('20B',mav.mav.system_time_encode(time_unix_usec, time_boot_ms).pack(mav.mav))
print(x)
mav.mav.system_time_send(time_unix_usec, time_boot_ms)
