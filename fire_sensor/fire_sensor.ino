// http://www.mrmodder.com visits for more Arduino Projects //
int Buzzer = 13; // Use buzzer for alert 
int FlamePin = 2; // This is for input pin
int smokePin = 3;
 // HIGH when FLAME Exposed
 
void setup() {
 pinMode(Buzzer, OUTPUT);
 pinMode(FlamePin, INPUT);
 pinMode(smokePin, INPUT);
 Serial.begin(9600);
 
}
 
void loop() {
 //Flame = digitalRead(FlamePin);
 if (digitalRead(FlamePin)== LOW||digitalRead(smokePin)== LOW)
 {
  Serial.println("HIGH FLAME");
  digitalWrite(Buzzer, HIGH);
 }
 
 else
 {
 Serial.println("No flame");
 digitalWrite(Buzzer, LOW);
 }
}
