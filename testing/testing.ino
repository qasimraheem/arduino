//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 3;
bool pinarray[8];

void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    Serial.begin(9600);
    setAllPins(0);
  // put your setup code here, to run once:

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
//binery to decimal convertor (convert pinarray into decimal number)
uint8_t btod(){
  uint8_t result=0;
  for(int i=0;i<8;i++){
    result+=MyPow(2,i)*pinarray[i];
    Serial.println(pinarray[i]);
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
void setPin(uint8_t pinNumber,bool power){
  pinarray[pinNumber]=power;
}
void setAllPins(bool power){
  for(int i=0;i<sizeof(pinarray)/sizeof(pinarray[0]);i++){
    pinarray[i]=power;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  setAllPins(0);
  setPin(1,1);
  setPin(2,1);
  setPin(3,0);
  setPin(4,0);
  setPin(5,0);
  setPin(6,0);
  if(true)
    {
      
       // take the latchPin low so 
       // the LEDs don't change while you're sending in bits:
       digitalWrite(latchPin, LOW);
       // shift out the bits:
       uint8_t result;
       result=btod();
       shiftOut_function(dataPin,  clockPin, MSBFIRST,result);
       //take the latch pin high so the LEDs will light up:
       digitalWrite(latchPin, HIGH);
 
       delay(10000);
   }

}
