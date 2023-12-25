
int LEDPin=13;      // LED is on pin 13
int buttonPinUp = 2;  // button sits on pin 2
int buttonStateUp;    // keeps track of Upbutton
int buttonPinDown = 3;  // button sits on pin 3
int buttonStateDown;    // keeps track of Downbutton
//int delayTime = 1000;      //how long time between blinks; used in delays
int delayStep = 100; //how much to change delaytime; used when button pressed

bool ledState = LOW;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;
unsigned long currentMillis;

void setup() {
  // initialize digital pin LEDPin as an output.
  pinMode(LEDPin, OUTPUT);
  pinMode(buttonPinUp, INPUT_PULLUP);
  pinMode(buttonPinDown, INPUT_PULLUP);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
//INPUT:
  buttonStateUp=digitalRead(buttonPinUp);
  buttonStateDown=digitalRead(buttonPinDown);
//LOGIC:

  currentMillis = millis();

  if (buttonStateUp = 1){
    currentMillis = currentMillis + delayStep;
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      //ledState=!ledState;
    digitalWrite(LEDPin, ledState);
    Serial.print(currentMillis);
    }
  }
  /*if(buttonStateUp==0) {
    delayTime = delayTime + delayStep;
    if(delayTime > 1000){
      delayTime = 1000;
    }
  }
  delayTime = constrain(delayTime, 0, 1000);

  if(buttonStateDown==0) {
    delayTime = delayTime - delayStep;
    if(delayTime < 0){
      delayTime = 0;
    }  
  }*/
//OUTOUT:
  Serial.print(buttonStateUp);
  Serial.print("\t");
  Serial.print(buttonStateDown);
  Serial.print("\t");
  /*Serial.println(delayTime);
  digitalWrite(LEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delayTime);                       // wait for a second
  digitalWrite(LEDPin, LOW);    // turn the LED off by making the voltage LOW
  delay(delayTime);   */                    // wait for a second
}
