#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
#include<Servo.h>
Servo myServo;
 String IncomingString="";
 const int lm35_pin = A0;
 int R=13,G=12,B=8;
 int photocellPin = A1;
 int photocellReading;
 float temp_val;
 bool smart=true;
 
 //Pin connected to SH_CP of 74HC595
int clockPin = 10;
 //Pin connected to ST_CP of 74HC595
int latchPin = 9;
////Pin connected to DS of 74HC595
int dataPin = 5;
bool gate=false;
bool pinarray[16];
void setup()
{
   myServo.attach(11);
 Serial.begin(9600);
 mySerial.begin(9600);
 delay(1000);
 pinMode(13,OUTPUT);
  pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
    setAllPins(0);
    myServo.write(120);
 }
 void toggleGate(){
  if(gate==false){
      myServo.write(120);
      gate=true;
    }else{
        myServo.write(170);
        gate=false;
    }
  }
  void toggleSmart(){
  if(smart==false){
      smart=true;
    }else{
        smart=false;
    }
  }
void loop(){
//  

delay(1000);
  readesp();

  uploadPins();
  light();
  temp();
//  if(IncomingString=="01"){
//    digitalWrite(13,HIGH);
//    }
 }
void sendSensorData(){
//  Tsensor=temp_val;
String Lsensor=String(photocellReading);
//  mySerial.write();
  mySerial.write(photocellReading);
}
void light(){
  photocellReading = analogRead(photocellPin);

if (photocellReading <= 200) {
 Serial.println("DARK : Analog Value = " + String(photocellReading));
 setAllPins(1); 
 }
 else if (photocellReading > 200 && photocellReading <= 500) {
 Serial.println("DIM LIGHT : Analog Value = " + String(photocellReading));
 setOddPins(1);
 } 
 else if (photocellReading > 500 && photocellReading <= 800) {
 Serial.println("BRIGHT LIGHT : Analog Value = " + String(photocellReading));
 setAllPins(0);  
 } 
 else if (photocellReading > 800) {
 Serial.println("FULL DAY LIGHT : Analog Value = " + String(photocellReading)); 
 } 
 
 delay(1000);
 }
 void temp(){
  int temp_adc_val;
  temp_adc_val = analogRead(lm35_pin);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  delay(1000);
  }
 void readesp(){
 boolean StringReady = false;
 
 while (mySerial.available()){
   IncomingString=mySerial.readString();
   StringReady= true;
     sendSensorData();
  }
 
  if (StringReady){
    Serial.println("Received String: " + IncomingString);
    if(IncomingString=="RO"){
        Serial.println("RGB");
        digitalWrite(R,LOW);
        digitalWrite(G,LOW);
        digitalWrite(B,LOW);
      }
      else if(IncomingString=="RR"){
        digitalWrite(R,HIGH);
        digitalWrite(G,LOW);
        digitalWrite(B,LOW);
      }
      else if(IncomingString=="RG"){
        digitalWrite(R,LOW);
        digitalWrite(G,HIGH);
        digitalWrite(B,LOW);
      }
      else if(IncomingString=="RB"){
        digitalWrite(R,LOW);
        digitalWrite(G,LOW);
        digitalWrite(B,HIGH);
      }
      else if(IncomingString=="RY"){
        digitalWrite(R,HIGH);
        digitalWrite(G,HIGH);
        digitalWrite(B,LOW);
      }
      else if(IncomingString=="RV"){
        digitalWrite(R,HIGH);
        digitalWrite(G,LOW);
        digitalWrite(B,HIGH);
      }
      else if(IncomingString=="RS"){
//        mySerial.write("RS",2);
        digitalWrite(R,LOW);
        digitalWrite(G,HIGH);
        digitalWrite(B,HIGH);
      }
      else if(IncomingString=="RW"){
        digitalWrite(R,HIGH);
        digitalWrite(G,HIGH);
        digitalWrite(B,HIGH);
      }
      else if(IncomingString=="GD"){
       toggleGate();
      }
      else if(IncomingString=="AA"){
       toggleSmart();
      }
      else if((IncomingString.toInt()>-1)&&(IncomingString.toInt()<64)){
        togglePin(IncomingString.toInt());
        sendSensorData();
        Serial.println("here");
      }
      else{}
      
    }
  }

  //shiftpins code
  void shiftOut_function(uint16_t dataPin, uint16_t clockPin, uint16_t bitOrder, uint16_t val)
{
      uint16_t i;

      for (i = 0; i < 16; i++)  {
            if (bitOrder == LSBFIRST)
                  digitalWrite(dataPin, !!(val & (1 << i)));
            else      
                  digitalWrite(dataPin, !!(val & (1 << (15 - i))));
                  
            digitalWrite(clockPin, HIGH);
            digitalWrite(clockPin, LOW);            
     } 
}
//binery to decimal convertor (convert pinarray into decimal number)
uint16_t btod(){
  uint16_t result=0;
  for(int i=0;i<16;i++){
    result+=MyPow(2,i)*pinarray[i];
//    Serial.println(pinarray[i]+1);
  }
  return result;
 }
//power function
int MyPow(int a, int b){
  if(b==0)
    return 1;
  else if(b==1)
    return a;
  else
    return a*MyPow(a,b-1);
}
//set array of pins
void setPin(uint16_t pinNumber,bool power){
  pinarray[pinNumber]=power;
}
void setAllPins(bool power){
  for(int i=0;i<sizeof(pinarray)/sizeof(pinarray[0]);i++){
    pinarray[i]=power;
  }
}
void setOddPins(bool power){
  for(int i=0;i<sizeof(pinarray)/sizeof(pinarray[0]);i++){
    if(i%2==0)
    {
      pinarray[i]=power;
    }
  }
}
void togglePin(uint16_t pinNumber){
 pinarray[pinNumber]=!pinarray[pinNumber];
  }
void uploadPins(){
   digitalWrite(latchPin, LOW);
       // shift out the bits:
       uint16_t result;
       result=btod();
       shiftOut_function(dataPin,  clockPin, MSBFIRST,result);
       //take the latch pin high so the LEDs will light up:
       digitalWrite(latchPin, HIGH);
  }
