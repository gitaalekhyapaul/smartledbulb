/*Created by Gita Alekhya Paul*/
#include <SoftwareSerial.h>

#define  Red_LED_Pin 9 // PWM Pin for Red LED
#define Green_LED_Pin 10 // PWM Pin for Green LED
#define Blue_LED_Pin 11 // PWM Pin for Blue LED
SoftwareSerial BTSerial(5,6); 

//Varibles to hold brightness values ranging from 0 (off) to 255 (fully on)
//int Red_value=0;
//int Green_value=0;
//int Blue_value=0;

char BData; // the data received from bluetooth serial link
int inPwr;

void setup() {
  
  // Initialise LED pins as outputs
  pinMode(Red_LED_Pin, OUTPUT);
  pinMode(Green_LED_Pin, OUTPUT);
  pinMode(Blue_LED_Pin, OUTPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);

  //initialsie serial communication
  BTSerial.begin(38400);
  Serial.begin(9600);
}

void loop() {

  //Process any info coming from the bluetooth serial link
  if(BTSerial.available()>0){
    BData=BTSerial.read(); //Get ID character from bluetooth to check
    if(BData=='L')inPwr=0;//Init for new command
    while(1){
      BData=BTSerial.read();
      if(BData=='\n')break;
      if(BData==-1)continue;
      inPwr*=10;
      inPwr=((BData-48))+inPwr;
    }
    if(inPwr>=0&&inPwr<=255){
      Serial.print('R');
      Serial.println(inPwr);
      analogWrite(Red_LED_Pin,inPwr);
    }
    else if(inPwr>=256&&inPwr<=511){
      inPwr-=256; //Necessary adjustment done in order to fit analogWrite()
      Serial.print('G');
      Serial.println(inPwr);
      analogWrite(Green_LED_Pin,inPwr);
    }
    else{
      inPwr-=512; //Necessary adjustment done in order to fit analogWrite()
      Serial.print('B');
      Serial.println(inPwr);
      analogWrite(Blue_LED_Pin,inPwr);
    }
    /*if(BluetoothData=='R') Red_value=BTSerial.parseInt(); //Read Red value
    if(BluetoothData=='G') Green_value=BTSerial.parseInt(); //Read Green Value
    if(BluetoothData=='B') Blue_value=BTSerial.parseInt(); //Read Blue Value*/
  }
  
  //update LED Brightness
  /*analogWrite(Red_LED_Pin, Red_value);
  analogWrite(Green_LED_Pin, Green_value);
  analogWrite(Blue_LED_Pin, Blue_value);
  delay(10);*/
  
}
