import serial
 
ser = serial.Serial(port = "/dev/ttyUSB0", baudrate=9600)
ser.close()
ser.open()
if ser.isOpen():
    print "Serial is open!"
    ser.write("Hello World!")
ser.close()
