import numpy as np
import cv2
import serial
import io
from time import sleep

ser  = serial.Serial('COM6',9600, timeout=0)

cap = cv2.VideoCapture(0)#đọc video từ camera trên máy tính(đặt chỉ số là 0)

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')#tạo ra đối tượng face_cascade để xử lý quán trình nhận diện khuôn mặt bên dưới

def chuyenDoi(s):
    i = 0;
    for j in str(s):
        i = i*10 + int(j);
    return i;
while(True):

    data = ser.readline();
    m = data.decode('utf-8');
    #number = chuyenDoi(s);
    #print(type(chr(number)))
    #print(m)
    # Capture frame-by-frame
    ret, frame = cap.read()
    # Our operations on the frame come here
    #grayImage = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    #cv2.imshow('Show', grayImage)
    faces = face_cascade.detectMultiScale(frame)#phương thức detect

    # Display the resulting frame

    #print (faces.shape)#in ra (N hàng, 4 cột) với N là số khuôn mặt còn 4 cột là 4 kích thước của hình chữ nhật
    print (faces) #in ra ma trận số ảnh = số hàng và kích thước và vị trí của ảnh cạnh ứng với 1 ảnh gồm tọa độ (x,y) và kích thước ảnh (w,h)
    if len(faces) == 0:
        print ('khong co mat nao')
        s = '0' + str(0) + '\n'
        ser.write(s.encode('utf-8'))
    else:
        print('Co mat')
        for (x,y,w,h) in faces:
            s = '0' + str(x) + '\n'
            
            if (x > 0 & x < 600):
              ser.write(s.encode('utf-8'))
            #ser.write(b'xy')
              ser.flush()# ham cho gui cho xong
               
            #sleep(0.01)
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),1)#sau for thì lệnh thực hiện phải tụt vào lề và enter xuống
            #if cv2.waitKey(1) & 0xFF == ord('q'):
       #break# When everything done, release the capture
    cv2.imshow('nhan dien', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):# đợi 1 mini giây tại dòng lệnh này và nếu phím q được nhấn thì thoát khỏi chương trình với lệnh break
      break
    #cv2.waitKey(0)
cap.release()
cv2.destroyAllWindows()
