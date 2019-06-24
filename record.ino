#define PIN_GATE_IN 2 // DB chekcer
//decibelcheckandrecord.ino
#define IRQ_GATE_IN 0 // DB checker
#define PIN_LED_OUT 13 //  DB checker
#define PIN_ANALOG_IN A0 // DB checker

int REC = 8; // recorder
int PLAYE = 9; // recorder
char input = 0; // recorder

void soundISR() // DB checker
{
 int pin_val;

 pin_val = digitalRead(PIN_GATE_IN); 
 digitalWrite(PIN_LED_OUT, pin_val); 
}

void setup()
{
 Serial.begin(9600);
 pinMode(REC,OUTPUT); // Recorder
 pinMode(PLAYE,OUTPUT); // Recorder
 
 pinMode(PIN_LED_OUT, OUTPUT); // DB checker LED OUTPUT
 pinMode(PIN_GATE_IN, INPUT); // DB checker
 attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE); //DB checker

 Serial.println("Initialized"); // DB checker Initialized
}

void loop()
{
 // DB checker from here
 int value; // DB checker

 value = analogRead(PIN_ANALOG_IN);

 Serial.print(value);
 Serial.print("Status: ");
 if(value <= 100)
 {
 Serial.println("Quiet.");
 }
 else if( (value > 100) && ( value <= 300) )
 {
 Serial.println("Moderate.");
 }
 else if(value > 300)
 {
 Serial.println("Loud.");
 }

 delay(1000);
 
  // recorder from here
 while(Serial.available()){
  input = Serial.read();
  if(value>300)
    input='P'; // when loud
  switch(input){
    case 'R':
      digitalWrite(REC,HIGH);
      break;
    case 'S':
      digitalWrite(REC,LOW);
      break;
     case 'P':
      digitalWrite(PLAYE,HIGH);
      delay(10);
      digitalWrite(PLAYE,LOW);
      break;
  }
 }
}
//egg
