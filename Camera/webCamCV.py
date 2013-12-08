import cv,os,random,serial 
#serial installed with pyserial
#sudo chown -R `whoami` /opt/local is my friend

ser = serial.Serial('/dev/tty.usbmodemfd121',9600)

def getSerialOutput(ser):
	return ser.readline()

#

def takePhoto():
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
