const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to, use to change the value of the outputValue with potentiometer
const int analogOutPin = 9; // Analog output pin that the LED is attached to, use to send value to LED to change brightness

int sensorValue = 0;        // value read from the potentiometer to then change the value of outputValue
int outputValue = 0;        // value output to the PWM (Pulse Width Modulation - gets analog results with digital means)(analog out) - the value will determine the LED's brightness

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
}

void loop() {
  //INPUT:
  // read the analog in value (A0):
  sensorValue = analogRead(analogInPin);

  //LOGIC:
  // map it to the range of the analog out, converts analogRead value(0-1023) to analogWrite value(0-255):
  // analogRead value comes from the potentiometer and it converts into the analogWrite value which is the LED
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  //outputValue = constrain(outputValue,0,128); // outputValue can only output half of what it can, LED can only get half of 100% brightness
  // change the analog out value:
  analogWrite(analogOutPin, outputValue); //LED from analogOutPin reads the outputValue and writes the value in the LED
  
  //OUTPUT:
  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
