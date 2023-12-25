const int PMPins[] = { A0,A1,A2 }; // Analog input pins that the potentiometers is attached to, is used to change the values of the outputValue with potentiometers
const int RGBPins[] = { 9,10,11 }; // Analog output pins that the RGB LED is attached to, is used to send value to RGB LED to change brightness on the different colors

int sensorValue = 0; // reads the value from each potentiometer, each sensorValue is attached to an outputValue, the potentiometer will then be used to chnage its connected outputValue
int outputValue = 0; // value output to the PWM (Pulse Width Modulation - gets analog results with digital means)(analog out) - the value will determine each colors brightness depending on its individual sensorValue.

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);

  // Loop on all pins ( 3 values: Red, Green and Blue )
  // Each number from "i" (0,1,2) will assign a potentiometer to a color, for example i=0 means potentiometer on pin A0 is assigned to color red (pin 9). After done assigning the "i" will be added on with a 1 because of (i++) ans the assigning steps repeats
  for (int i = 0; i < 3; i++){
    pinMode(PMPins[i], INPUT); // sets the PMPins (Potentiometer pins) as input pins
    pinMode(RGBPins[i], OUTPUT); // sets theRGBPins as output pins
  }
}

void loop() {

  for (int i = 0; i < 3; i++){
    //INPUT:
    sensorValue = analogRead(PMPins[i]); // reads the analog in values or the values of the potentiometers 
    
    //LOGIC:
    // Scale down the potentiometer reading ( 0 ~ 1023 ) to a valid PWM value (0-255). PWM value is read by the RBG LED (for each color, from each PM)
    outputValue = map(sensorValue, 0, 1023, 0, 255);

    //OUTPUT:
    // Write the output on the pin
    analogWrite(RGBPins[i], outputValue);
  }
}
