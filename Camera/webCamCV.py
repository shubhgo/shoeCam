import cv,os,random,serial 
#serial installed with pyserial
#sudo chown -R `whoami` /opt/local is my friend

ser = serial.Serial('/dev/tty.usbmodemfd121',9600)
#or ser = serial.Serial('/dev/tty.usbmodemfa131',9600)

def getSerialOutput(ser):
	"""If Serial returns c, takes a photo and halts."""
	while True: 
		r = ser.read()
		if r == "c":
			takePhoto()
		break
	return 

#

def takePhoto():
	"""Takes a photo with webcam and gives it a name with a random number. Saves photo to current
	directory."""
	photoName = "IMG_"+random.randint(1,900) + ".jpg" #idk if we want to change this later
	
	cv.NamedWindow("w1", cv.CV_WINDOW_AUTOSIZE)
	camera_index = 1 #changed to 1, since was taking photo with build in webcam
	capture = cv.CaptureFromCAM(camera_index)

	frame = cv.QueryFrame(capture)
	cv.SaveImage(photoName, frame)
	print "Photo saved to",os.getcwd()+"/"+photoName
	return


'''

for i in range(3):
	capture = cv.CaptureFromCAM(i)
	if capture:
		break

# capture = cv.CaptureFromCAM(0)

def repeat():
	frame = cv.QueryFrame(capture)
	cv.ShowImage("w1", frame)
	c = cv.WaitKey(10)

while True:
	repeat()
'''
