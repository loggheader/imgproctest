import cv2
import numpy as np
import sys


image=cv2.imread("/home/mpourmpoulis/Pictures/helphelp/help/t1.png")
image=cv2.resize(image,(200,200))
oime=cv2.Canny(image,int(sys.argv[1]),int(sys.argv[2]))
cv2.imwrite("nothing.jpg",oime)
cv2.waitKey(0)
