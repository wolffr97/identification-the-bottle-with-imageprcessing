import numpy as np
import cv2
import math
import serial
arduino = serial.Serial('COM6', 9600)
# arduino = serial.Serial('COM5', 9600)
chup =0;
cap = cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)
tong=0
data=0
def pythonreply(para):
    msg = str(para)
    arduino.write(bytes(msg))
    print(msg)
while True:
    length=0
    ret, img = cap.read()
    data = arduino.read()
    data = str(data)
    key = cv2.waitKey(10)    
    ret, img = cap.read()
    if img is None:
         break
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 200, 220)
    lines = cv2.HoughLinesP(edges, 1, math.pi/1, 10, 10, 2, 350);

    dot1 = (lines[0][0][0],lines[0][0][1])
    dot2 = (lines[0][0][2],lines[0][0][3])
    cv2.line(img, dot1, dot2, (0,0,255), 3)
    cv2.imshow("output", img)
   # print (length)
    key = cv2.waitKey(10)
   
    if key == 27:
         break
    if data=="c":
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        edges = cv2.Canny(gray, 100, 120)
        lines = cv2.HoughLinesP(edges, 1, math.pi/1, 20, None, 2, 480);

        dot1 = (lines[0][0][0],lines[0][0][1])
        dot2 = (lines[0][0][2],lines[0][0][3])
        cv2.line(img, dot1, dot2, (0,0,255), 3)
        cv2.imshow("output", img)
        length = lines[0][0][1] - lines[0][0][3]      
        print(length)
        if(length<180 or length>220):
            print("khong dat")
            pythonreply(0)
            data="kc"
        elif(length>=180 and length<=220):
            print("dat")
            pythonreply(1)
            data="kc" 
        length=0    
cv2.destroyAllWindows() 
cv2.VideoCapture(0).release()