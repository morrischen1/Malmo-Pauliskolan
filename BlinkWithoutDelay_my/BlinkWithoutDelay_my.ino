const int ledPin =  13;// the number of the LED pin

int  buttonPinDown = 2; //button sits on pin 2
int  buttonPinUp = 3;   //button sits pn pin 4
int  buttonStateDown;   //keeps track of the buttons status
int  buttonStateUp;     //keeps track of the buttons status
int  delayStep = 100;   //how much the delay is changed whenever the button is pushed
int ledState = LOW;             // ledState used to set the LED
bool ledStateONOFF = LOW;
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
int delayTime = 1000;           // interval at which to blink (milliseconds)
unsigned long currentMillis;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPinDown, INPUT_PULLUP);
  pinMode(buttonPinUp, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  //INPUT:
  buttonStateDown = digitalRead(buttonPinDown);
  buttonStateUp = digitalRead(buttonPinUp);
  //LOGIC:
  if (buttonStateDown == 0) { //button for lowering the delay has been pressed
    delayTime = delayTime - delayStep;
    delay(200);
  }
  if (buttonStateUp == 0) { //button for increasing the delay has been pressed
    delayTime = delayTime + delayStep;
    delay(200);
  }
  delayTime = constrain(delayTime, 0, 2000);

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  currentMillis = millis();

  if (currentMillis - previousMillis >= delayTime && ledStateONOFF == HIGH) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    ledState=!ledState;
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

  if (buttonStateUp == 0 && buttonStateDown == LOW){
    ledStateONOFF=!ledStateONOFF;
  }

  Serial.print("\t");
  Serial.print("Delay: ");
  Serial.print(delayTime);
  Serial.println("\t");
}
