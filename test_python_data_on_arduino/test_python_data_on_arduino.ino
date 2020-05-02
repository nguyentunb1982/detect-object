#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,7);
int i = 0;int datah = 1;
String dataString = "";
int dataxuat =0;
int inA1 = 2;//inA1 giống như chân MT1 (chỉ là cách đặt tên thôi)
int inA2 = 3;//inA2 giống như chân MT2
int inB1 = 4;//inB1 giống như chân MT3
int inB2 = 5;//inB2 giống như chân MT4
int pwa = 9;
int pwb = 10;
//int toado_x = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);Serial.begin(9600);
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
pinMode(13,OUTPUT);
digitalWrite(13,LOW);
  pinMode(pwa, OUTPUT);
  pinMode(pwb, OUTPUT);
mySerial.begin(9600);
}
int chuyendoi(String s){
  int i = 0;
   for (int j = 0;j<s.length();j++){
    char x = s.charAt(j);
      i = i*10 + atoi(x);
      } 
  return i;
  }
void chuyendong(int x){
  
  if ( x < 250 && x>190){ 
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
    delay(5);
   }
//quay phai
  if (x < 190){
    analogWrite(pwa, 90);analogWrite(pwb, 100);
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
    delay(5);
    }
  
  //quaytrai;
  if (x > 250){
    analogWrite(pwa, 90);analogWrite(pwb, 100);
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, LOW);
    digitalWrite(inB2, HIGH);
    delay(5);
    }
  if (x == 0){
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, LOW);
    digitalWrite(inB2, LOW);
    delay(5);
    }
}
void nextionSet(String object, String data)
{
  String command = String(object) + String("=\"") + data + String("\"");
  mySerial.print(command);
  mySerial.write(0xff);
  mySerial.write(0xff);
  mySerial.write(0xff);
  Serial.println(command);
}

void nextionSet(String object, int data)
{
  String command = String(object) + String("=") + data;
  mySerial.print(command);
  mySerial.write(0xff);
  mySerial.write(0xff);
  mySerial.write(0xff);
}


void loop() {
  
  while(Serial.available()>0){
      //int datatupc = Serial.read(); 
      //nextionSet(String("n0") + String(".val"), datatupc);
      
        //dataString += (char)datatupc; 
        //int x = dataString.toInt();
        //nextionSet(String("n0") + String(".val"), x);
        //if (dataString == "4"){delay(10);digitalWrite(13,HIGH);}
        //dataString = "";
    //delay(50);    
    String datatupcchuoi = Serial.readStringUntil('\n');
    //nextionSet("page0.t0.txt", String(datatupcchuoi));
    if (datatupcchuoi.length() <= 4){ 
    int toado_x = datatupcchuoi.toInt();
    nextionSet(String("n0") + String(".val"), toado_x);
    chuyendong(toado_x);
   
    //quaytrai(toado_x);
    
    //dithang(toado_x);}
    }
     }
}
