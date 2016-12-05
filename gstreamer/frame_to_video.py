#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2
import os.path
img = cv2.imread('server_00000350.png')
height , width , layers =  img.shape
print("height",height)
print("width",width)
i = 350
count = 700
fourcc = cv2.cv.CV_FOURCC(*'MJPG')
video = cv2.VideoWriter('server.avi',fourcc,15,(width,height))
while (i < count):
    image_name = "server_%08i.png"%i
    if os.path.exists(image_name):
        img = cv2.imread(image_name)
	#print("imread: ",image_name)
	video.write(img)
	#print("video.write: ",image_name)
    else:
	print("no exists: ",image_name)
    i += 1

#cv2.destroyAllWindows()
video.release()
