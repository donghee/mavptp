import serial

#ser = serial.Serial("/dev/tty.usbmodem1", 57600)
ser = serial.Serial("/dev/ttyACM0", 57600)
ser.setDTR()
ser.flushInput()
count = 0
while True:
   try:
       count += 1
       x = ser.read()
       print '%d:'%count,x,' (dec %d'%ord(x),' hex %x)'%ord(x)
   except KeyboardInterrupt:
      ser.close()
      print '%s is closed'%port
      sys.exit()
