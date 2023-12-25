const int analogPin = A0;   // the pin that the potentiometer is attached to
const int BGLED = 10;    // the number of LEDs in the bargraph
int sensorValue;      //raw value from potentiometer
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};   // an array of pin numbers to which LEDs are attached
int LEDLevel; //the Led level, vill be used to determine which led wil be on and off

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  // loop over the pin array and set them all to output:
  // Every Led will be assigned to a pin, in numerical order
  for (int CurrentLed = 0; CurrentLED < BGLED; CurrentLED++) {
    pinMode(ledPins[CurrentLED], OUTPUT);
  }
}

void loop() {
  //INPUT:
  // read the value from potentiometer:
  sensorValue = analogRead(analogPin);

  //LOGIC:
  // LEDLevel is the mapped  result of a range from 0 to the number of LEDs:
  LEDLevel = map(sensorValue, 0, 1023, 0, BGLED);

  // loop over the LED array:
  for (int CurrentLED = 0; CurrentLED < BGLED; CurrentLED++) {
  
  //OUTPUT:
    // if the array element's index (current LED) is less than LEDLevel, turn the pin for this element on:
    if (CurrentLED < LEDLevel) {
      digitalWrite(ledPins[CurrentLED], HIGH);
    }
    // turn off all pins higher than the LEDLevel:
    else {
      digitalWrite(ledPins[CurrentLED], LOW);
    }
  }
}
