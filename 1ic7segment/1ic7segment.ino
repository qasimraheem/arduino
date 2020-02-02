//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 7;
////Pin connected to DS of 74HC595
int dataPin = 3;
bool pinarray[8];
int center=1;
int topLeft=2;
int top=3;
int topRight=4;
int bottumLeft=5;
int bottum=6;
int bottumRight=7;
int numbers [10][8]={{2,3,4,5,6,7,0},{4,7,0,0,0,0,0},{3,4,5,6,1,0,0},{3,4,6,7,1,0,0},{1,2,4,7,0,0,0},{1,2,3,6,7,0,0},{1,2,3,5,6,7,0,0},{3,4,7,0,0,0,0},{1,2,3,4,5,6,7,0},{1,2,3,4,6,7,0}};

void setup() 
{
    //set pins to output so you can control the shift register
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    Serial.begin(9600);

}

//code for shiftOut function

void shiftOut_function(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
      uint8_t i;

      for (i = 0; i < 8; i++)  {
            if (bitOrder == LSBFIRST)
                  digitalWrite(dataPin, !!(val & (1 << i)));
            else      
                  digitalWrite(dataPin, !!(val & (1 << (7 - i))));
                  
            digitalWrite(clockPin, HIGH);
            digitalWrite(clockPin, LOW);            
     } 
}
uint8_t btod(){
  uint8_t result=0;
  for(int i=0;i<8;i++){
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
void setPin(uint8_t pinNumber,bool power){
 pinarray[pinNumber]=power;
 }
void displayLed(int number){
  for(int i=0;i<8;i++){
    setPin(i,1);
  }
  if(number<=9){
    for(int i=0;i<8;i++){
      setPin(numbers[number][i],0);
    }
  }
  
  
}
void printarray(){
  for(int i=0;i<8;i++){
    Serial.println(pinarray[i]);
    }
  }
void loop() 
{
    for (int display_number = 0; display_number <= 9; display_number++) 
    {     
      setPin(1,1);
       digitalWrite(latchPin, LOW);
       uint8_t result;
       displayLed(display_number);
       result=btod();
       Serial.println(result);
       shiftOut_function(dataPin,  clockPin, MSBFIRST,result);
       digitalWrite(latchPin, HIGH);
       delay(1000);
   }
}
