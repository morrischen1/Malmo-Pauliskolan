const int analogInPin = A0; //photoresistors pin is A0
const int analogOutPin = 3; //LED pin is 3
int maxLevel = 0; //
int minLevel = 1023;
const int buttonPin = 2;
int buttonState;
int sensorValue = 0; 
int outputValue = 0;

void setup() { 
  Serial.begin(115200); 
  pinMode(analogInPin, INPUT);
  pinMode(analogOutPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  }

void loop() { 
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(analogInPin); //sensorValue analogreads analogInPin value
  sensorValue = constrain(sensorValue,0,1023); //sensorValue gets a barrier between 0-1023
  outputValue = map(sensorValue, 0, 1023, 0, 255); //mapped value of sensorValue
  outputValue = constrain(outputValue,0,255); //outputValue gets a barrier between 0-255
  analogWrite(analogOutPin, outputValue);
 
  if (buttonState == LOW) { //if button is pressed, everything down below the if function will happen
    maxLevel=max(maxLevel, outputValue);
    minLevel=min(minLevel, outputValue);
    Serial.print("Current Value:");
    Serial.println(outputValue);
    Serial.print("Max value:");
    Serial.println(maxLevel);
    Serial.print("Min value:");
    Serial.println(minLevel);
    Serial.println("------------");
    delay(100);
  }
   
  else { //else or if button is not pressed, everything below this else function will happen 
    Serial.print("Current Value:");
    Serial.println(outputValue);
    Serial.println("------------");
    delay(100); 
    }
}
