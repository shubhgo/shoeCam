import cv

cv.NamedWindow("w1", cv.CV_WINDOW_AUTOSIZE)
camera_index = 0
capture = cv.CaptureFromCAM(camera_index)

frame = cv.QueryFrame(capture)
cv.SaveImage("pic.jpg", frame)


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