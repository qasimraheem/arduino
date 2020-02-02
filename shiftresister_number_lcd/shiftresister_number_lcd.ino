//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 7;
////Pin connected to DS of 74HC595
int dataPin = 3;
bool pinarray[16];
int center=1;
int topLeft=2;
int top=3;
int topRight=4;
int bottumLeft=5;
int bottum=6;
int bottumRight=7;
int numbers [10][8]={{2,3,4,5,6,7,0},{4,7,0,0,0,0,0},{3,4,1,6,5,0,0},{3,4,6,7,1,0,0},{1,2,4,7,0,0,0},{1,2,3,6,7,0,0},{1,2,3,5,6,7,0,0},{3,4,7,0,0,0,0},{1,2,3,4,5,6,7,0},{1,2,3,4,6,7,0}}; 
void setup() 
{
    //set pins to output so you can control the shift register
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    Serial.begin(9600);

}

//code for shiftOut function

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
uint16_t btod(){
  uint16_t result=0;
  for(int i=0;i<16;i++){
    result+=MyPow(2,i)*pinarray[i];
    Serial.println(pinarray[i]+1);
    }
    
    return result;
  }

  int MyPow(int a, int b){
    if(b==0)
        return 1;
      else if(b==1)
        return a;
      else
        return a*MyPow(a,b-1);
    }
void setPin(uint16_t pinNumber,bool power){
 pinarray[pinNumber]=power;
 }
void displayLed(int number){
  for(int i=0;i<16;i++){
    setPin(i,1);
  }
  if(number<=9){
    for(int i=0;i<8;i++){
      setPin(numbers[number][i],0);
    }
}
  if(number>9){
    int remaining=number%10;
    int quesont=number/10;
    for(int i=0;i<8;i++){
      setPin((numbers[remaining][i]),0);
    }
    for(int i=0;i<8;i++){
      if(numbers[quesont][i]!=0){
        setPin((numbers[quesont][i]+7),0);
        }
    }
  }
  
}
void printarray(){
  for(int i=0;i<16;i++){
    Serial.println(pinarray[i]);
    }
  }
void loop() 
{
    // count from 0 to 255 and display the number 
    // on the LEDs
    
    for (int display_number = 0; display_number <= 100; display_number++) 
    {
       // take the latchPin low so 
       // the LEDs don't change while you're sending in bits:
       digitalWrite(latchPin, LOW);
       // shift out the bits:
       uint16_t result;
       
        displayLed(display_number);
  
        
       result=btod();
       shiftOut_function(dataPin,  clockPin, MSBFIRST,result);
       //take the latch pin high so the LEDs will light up:
       digitalWrite(latchPin, HIGH);
 
       delay(60000);
   }

}
