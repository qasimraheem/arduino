
const int buzzer = 3;
const int sensor = 2;
const int led = 4;
int ledgreen=5;
void setup() 
{
  pinMode(buzzer, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
  delay(5000);
  digitalWrite(led,LOW);
}
void loop()
{
  
    if(digitalRead(sensor) == HIGH)
    {
      digitalWrite(ledgreen, LOW);
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      delay(5000);
    }else
    {
      digitalWrite(buzzer, LOW);
        digitalWrite(ledgreen, HIGH);
    }
  
}
