//Code for the Master board
//#include<Wire.h>//This library is used for I2C communication

#include <IRremote.h> //Make sure to install the library


int IRpin=11; // IR Sensor  pin
int io = 2; // pin connect to lcd controller

volatile bool state;
IRrecv IR(IRpin);
decode_results cmd;



//String myCom;
//int countin =0;
//int ledr = 13;
//int ledg = 12;
//int io = 10;
//int a,b,c,d,e,f;
//unsigned long starttime,endtime, duration,x;

void setup() {
//  Wire.begin();
  Serial.begin(9600);
//  pinMode(ledr,OUTPUT);
//  pinMode(ledg,OUTPUT);
  pinMode(io,OUTPUT);
//  digitalWrite(io,0);
//  digitalWrite(ledr, 1);
//  delay(500);
//  digitalWrite(ledr,0);
//digitalWrite(io,HIGH);
digitalWrite(io,LOW);
IR.enableIRIn();
  delay(7000);
  state=0;
}
int count =0;
void loop() {
// starttime = millis();

      while(IR.decode(&cmd)==0){

    }
   
  state= !state;
  count ++;

//    Serial.print("STATE:  ");
//  Serial.println(state);
  digitalWrite(io,state);

 
  Serial.print("IO STATE :");
  Serial.println(digitalRead(io));
 
  Serial.print("SLAVE Detected :  ");
  Serial.println(count);
   delay(400);
//  digitalWrite(io,HIGH);
   Serial.println();

 IR.resume();

}
