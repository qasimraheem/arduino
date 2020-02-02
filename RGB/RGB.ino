
int temp;
void setup() {
  Serial.begin(9600);

  // put your setup code here, to run once:

  pinMode(A0,INPUT);
   pinMode(9,OUTPUT);
   pinMode(10,OUTPUT);
}

void loop() {
  temp=analogRead(A0);
  Serial.println(temp);
}
