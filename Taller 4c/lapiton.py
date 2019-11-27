import serial, time
timeout = time.time()+10
arduino = serial.Serial('COM3',9600)
time.sleep(2)
while time.time()<timeout:
	rawString = arduino.readline()
	print(rawString)
arduino.close()