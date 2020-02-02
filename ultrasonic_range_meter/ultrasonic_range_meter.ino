#include "pitches.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int trigPin = 11;
const int echoPin = 10;
const int led = 13;
int button = 12;
int lcdlight = 8;
byte light_on[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B01010,  
  B11011
};
byte light_off[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B01010,  
  B11011
}; 
void setup() 
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(button,INPUT);
  pinMode(lcdlight,OUTPUT);
  digitalWrite(lcdlight,HIGH);
  lcd.begin(16, 2);
  lcd.createChar (0, light_on);    // load smiley to memory 0
  lcd.createChar (1,light_off);
  lcd.setCursor(0,0); 
  lcd.print ("Ultrasonic ");
  lcd.setCursor(0, 1);
  lcd.print ("Range Meter");
  delay (5000);
  lcd.clear();
  lcd.print("Developed By");
  lcd.setCursor(0, 1);
  lcd.print ("   ");
  delay(4000);
  lcd.clear();
  lcd.print("Qasim Raheem ""And");
  lcd.setCursor(0,1);
  lcd.print("M.Tahseen");
  delay(5000);
  digitalWrite(lcdlight,LOW);
}
long duration, r;
float distance;
bool flag=false;
void loop()
{
  lcd.clear();
  lcd.print("Distance in cm");
    
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  long r = 3.4 * duration / 2;     
  float distance = r / 100.00;
  
  

  
 if(digitalRead(button) == HIGH)
 {
    digitalWrite(lcdlight,HIGH);
    
    if(flag == false)
    {
      lcd.clear();
      
      lcd.print(char(0));
      lcd.print("LCD Light ON");
      delay(800);
      flag=true;
    }
 }
 else
 {
    digitalWrite(lcdlight,LOW);
    if(flag == true)
    {
      lcd.clear();
      lcd.print(char(1));
      lcd.print("LCD Light OFF");
      delay(800);
      flag=false;
    }
 }

 
 if(distance<20)
  {
    digitalWrite(led,HIGH);
    lcd.setCursor(0, 1);
    lcd.print(distance);
    /*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/



// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }


    delay (500);
  }
  else if(distance>3000)
  {
    lcd.clear();
    lcd.print("Out of Range");
    delay(300);
  }
 else
  {
    lcd.setCursor(0, 1);
    lcd.print(distance);
    delay (300);
    digitalWrite(led,LOW);
  }
  
 delay(300);
}
