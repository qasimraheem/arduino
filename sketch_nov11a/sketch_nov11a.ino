//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 11;
////Pin connected to DS of 74HC595
int dataPin = 9;
bool pinarray[16];

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

void loop() 
{
    // count from 0 to 255 and display the number 
    // on the LEDs
    for (int display_number = 0; display_number < 65536; display_number++) 
    {
       // take the latchPin low so 
       // the LEDs don't change while you're sending in bits:
       digitalWrite(latchPin, LOW);
       // shift out the bits:
       uint16_t result;
       setPin(0,1);
       setPin(2,1);
       setPin(3,1);
       setPin(7,1);
       setPin(3,0);
       setPin(8,1);
       setPin(9,1);
       result=btod();
       Serial.println(result);
       shiftOut_function(dataPin,  clockPin, MSBFIRST,result);
       //take the latch pin high so the LEDs will light up:
       digitalWrite(latchPin, HIGH);
       // pause before next value:
       delay(50);
   }
//int val=1,i=1;
//digitalWrite(latchPin, LOW);
//digitalWrite(dataPin, !!(val & (1 << i)));
//digitalWrite(latchPin, HIGH);
}
