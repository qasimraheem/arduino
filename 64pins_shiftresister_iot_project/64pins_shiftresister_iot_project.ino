//Pin connected to SH_CP of 74HC595
int clockPin = 6;
//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to DS of 74HC595
int dataPin = 3;
bool pinarray[64];

void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    Serial.begin(9600);
  // put your setup code here, to run once:

}
//code for shiftOut function

void shiftOut_function(uint64_t dataPin, uint64_t clockPin, uint64_t bitOrder, uint64_t val)
{
      uint64_t i;

      for (i = 0; i < 64; i++)  {
            if (bitOrder == LSBFIRST)
                  digitalWrite(dataPin, !!(val & (1 << i)));
            else      
                  digitalWrite(dataPin, !!(val & (1 << (15 - i))));
                  
            digitalWrite(clockPin, HIGH);
            digitalWrite(clockPin, LOW);            
     } 
}
//binery to decimal convertor (convert pinarray into decimal number)
uint64_t btod(){
  uint64_t result=0;
  for(int i=0;i<64;i++){
    result+=MyPow(2,i)*pinarray[i];
    Serial.println(pinarray[i]+1);
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
void setPin(uint64_t pinNumber,bool power){
  pinarray[pinNumber]=power;
}
void setAllPins(bool power){
  for(int i=0;i<64;i++){
    pinarray[i]=power;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  
  if(true)
    {
       // take the latchPin low so 
       // the LEDs don't change while you're sending in bits:
       setAllPins(1);
       setPin(1,1);
       digitalWrite(latchPin, LOW);
       // shift out the bits:
       uint64_t result;
       result=btod();
       shiftOut_function(dataPin,  clockPin, MSBFIRST,result);
       //take the latch pin high so the LEDs will light up:
       digitalWrite(latchPin, HIGH);
 
       delay(10000);
   }
}
