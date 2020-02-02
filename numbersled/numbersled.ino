int center=2;
int topLeft=3;
int top=4;
int topRight=5;
int bottumLeft=6;
int bottum=7;
int bottumRight=8;

int numbers [10][8]={{3,4,5,6,7,8,0},{3,6,0,0,0,0,0},{4,5,6,7,2,0,0},{4,5,7,8,2,0,0},{2,3,5,8,0,0,0},{2,3,4,7,8,0,0},{2,3,4,6,7,8,0,0},{4,5,8,0,0,0,0},{2,3,4,5,6,7,8,0},{2,3,4,5,7,8,0}};
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(topLeft,OUTPUT);
  pinMode(top,OUTPUT);
  pinMode(topRight,OUTPUT);
  pinMode(bottumLeft,OUTPUT);
  pinMode(bottumRight,OUTPUT);
  pinMode(bottum,OUTPUT);
  pinMode(center,OUTPUT);
}
void displayLed(int number){
  for(int i=0;i<9;i++){
    digitalWrite(i,HIGH);
    }
  for(int i=0;i<8;i++){
    digitalWrite(numbers[number][i],LOW);
    }
  }
// the loop function runs over and over again forever
void loop() {
//  digitalWrite(topLeft, LOW);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(top, LOW);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(topRight, LOW);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(bottumLeft, LOW);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(bottumRight, LOW);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(bottum, LOW);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(center, HIGH);   // turn the LED on (HIGH is the voltage level)

for(int i=0;i<9;i++){
  displayLed(i);
  delay(1000);
  }
  

  
  
}
