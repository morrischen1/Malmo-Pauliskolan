const int analogOutPin = 9; // Analog output pin that the LED is attached to, use to send value to LED to change brightness
int valueState = 0;        // value from the buttons (which is different to the value sent to the LED) is set to 0
int outputValue = 0;        // value output to the PWM (Pulse Width Modulation - gets analog results with digital means)(analog out) - the value will determine the LED's brightness
int buttonPinUp = 7;        // Sets pin 7 for dimm up button
int buttonPinDown = 8;      // Sets pin 8 for dimm down button
int buttonStateUp;          // The state of dimm up button, will determine when the LED dimms up
int buttonStateDown;        // The state of dimm down button, will determine when the LED dimms down
const int valueStep = 10;   // Each time one of the button is pressed (or holds in) the valuestep will add or reduce on valueState (not same value as the LED (will be converted later on))

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  pinMode(buttonPinUp, INPUT_PULLUP);   //sets buttonPinUp as INPUT_PULLUP
  pinMode(buttonPinDown, INPUT_PULLUP); //sets buttonPinDown as INPUT_PULLUP
  pinMode(analogOutPin,OUTPUT);         //sets analogOutPin as OUTPUT
}

void loop() {
//INPUT
  buttonStateDown = digitalRead(buttonPinDown); //buttonStateDown digitalreads buttonPinDown, whenever buttonPinDown changes value (HIGH or LOW) so does buttonStateDown so that they have the same
  buttonStateUp = digitalRead(buttonPinUp);     //buttonStateUp reads buttonPinUp as digital, whenever buttonPinUp changes value (HIGH or LOW) so does buttonStateUp so that they have the same

//LOGIC  
  if (buttonStateUp == HIGH){     //An if function, if buttonStateUp is HIGH then the valueStep value will add into valueState, if constantly holding the button then the value will constantly go up
    valueState = valueState + valueStep;
  }
  if (buttonStateDown == HIGH){   //An if function, if buttonStateUp is HIGH then the valueStep value will reduce from valueState, if constantly holding the button then the value will constantly go down
    valueState = valueState - valueStep;
  }
  // map it to the range of the analog out, converts the stored digitalRead value(0-1023) to digitalWrite value(0-255)(LED's value):
  outputValue = map(valueState, 0, 1023, 0, 255);
  outputValue = constrain(outputValue,0,255); // outputValue gets an constrain on the min and max value (for LED) which is between 0 and 255 which is also what the LED can handle, sets the constrain so it doesn't print out value bigger than 255 and negative numbers
  valueState = constrain(valueState,0,1023);  //valueState gets an constrain on the min and max value (value added/reduced by the buttons), this value is used to convert to the outputValue (digitalWrite) (LED), even though its at the min and max of valueState's real values, it does prevent it printing out numbers bigger than real max value and negative values

//OUTPUT  
  //outputs the value for the LED after it being converted from valueState value, the LED will start dimming (if not it is at 0)
  analogWrite(analogOutPin,outputValue);

  // print the results to the Serial Monitor:
  Serial.print("valueState = ");
  Serial.print(valueState);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 0.1 seconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}
