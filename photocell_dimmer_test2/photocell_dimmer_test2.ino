const int analogInPin = A0; //photoresistors pin is A0
const int analogOutPin = 3; //LED pin is 3
int maxLevel = 0; //max raw value starting at 0 to then be adjusted with a higher number
int minLevel = 1023; //min raw value starting at 1023 to then be adjusted with a lower number
const int buttonPin = 2; //button is assigned to pin 2, will be used to show max-minLevel values
int buttonState; //the state of the button registered on pin 2
int sensorValue; //the raw value from photocell
int outputValue; //the mapped value outputed by analogOutPin
int margin = 10; //margin set at 10, will be used to completely turn off/on LED if outputValue is 10 (and less (>10)) away from 0/255 because of how inconsistent the values are sometimes

void setup() { 
  Serial.begin(115200); // initialize serial communications at 115200 bps:
  pinMode(analogInPin, INPUT); //analogInPin sets as input mode, will be inputted the raw value from photocell
  pinMode(analogOutPin, OUTPUT); //analogOutPin sets as output mode, will output mapped value of sensorValue
  pinMode(buttonPin, INPUT_PULLUP); //buttonPin sets as input_pullup mode, will be used to register max- and minLevel
  }

void loop() { 
  //INPUT:
  buttonState = digitalRead(buttonPin); //buttonState reads value of buttonPin, will be either HIGH or LOW
  sensorValue = analogRead(analogInPin); //sensorValue reads the value of analogInPin (analog pin only)
  
  //LOGIC:
  if (buttonState == LOW) { //if button is pressed (registers a 1)
    maxLevel=max(maxLevel, sensorValue); //assigns maxLevel to the larger maxLevel value or sensorValue, guarantees maxLevel to never pass sensorValue
    minLevel=min(minLevel, sensorValue); //assigns minLevel to the smaller minLevel value or sensorValue, guarantees minLevel will be atleast as the sensorValue
  }  
  outputValue = map(sensorValue, minLevel, maxLevel, 0, 255); //outputValue is the mapped value of sensorValue, fromLow = minLevel, fromHigh = maxLevel, toLow = 0, toHigh = 255
  outputValue = constrain(outputValue, 0, 255); //constrains outputValue, outputValue can only output values between 0-255
 
  if (outputValue <= margin){ //if outputValue has same value as margin or less (0-10), outputValue will automatically have the value 0
    outputValue = 0;
  }
  if (outputValue >= (255-margin)){ //if outputValue is between 245-255, outputValue will automatically have the value 255
    outputValue = 255;
  }
  
  //OUTPUT:
  analogWrite(analogOutPin, outputValue); //outputs the outputValue for the analogOutPin (LED)
  //prints the results in the Serial Monitor
  Serial.print("Current Value:");
  Serial.print(outputValue);
  Serial.print(" Max value:");
  Serial.print(maxLevel);
  Serial.print(" Min value:");
  Serial.println(minLevel);
  // wait 0.01 seconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(10); 
}
