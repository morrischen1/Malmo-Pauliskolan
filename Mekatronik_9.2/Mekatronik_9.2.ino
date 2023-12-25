int steeringPin = A4;
int speedPin = A5;

int steeringValue = 0;
int speedValue = 0;

float rightSteeringValue;
float leftSteeringValue;

int leftPolarity;
int rightPolarity;

void setup() {
  Serial.begin(9600);
  pinMode(steeringPin, INPUT);
  pinMode(speedPin, INPUT);
}

void loop() {
  steeringValue = analogRead(steeringPin);
  speedValue = analogRead(speedPin);

  if (steeringValue <= 257){
    leftSteeringValue = map(steeringValue, 0, 257, 255, 0);
    rightSteeringValue = map(steeringValue, 0, 257, 255, 255);
  }
  else if (steeringValue <= 512){
    leftSteeringValue = map(steeringValue, 256, 512, 0, 255);
    rightSteeringValue = map(steeringValue, 256, 512, 255, 255);
  }
  else if (steeringValue <= 767){
    leftSteeringValue = map(steeringValue, 512, 767, 255, 255);
    rightSteeringValue = map(steeringValue, 512, 767, 255, 0);
  }
  else if (steeringValue <= 1023){
    leftSteeringValue = map(steeringValue, 767, 1023, 255, 255);
    rightSteeringValue = map(steeringValue, 767, 1023, 0, 255);
    
  }

  if (steeringValue <= 256){
    leftPolarity = -1;
  }
  else {
    leftPolarity = 1;
  }

  if (steeringValue >= 768){
    rightPolarity = -1;
  }
  else {
    rightPolarity = 1;
  }
  
  rightSteeringValue = constrain(rightSteeringValue, 0, 255);
  leftSteeringValue = constrain(leftSteeringValue, 0, 255);
  speedValue = map(speedValue, 0, 1023, 0, 1000);
  leftSteeringValue = (leftSteeringValue/1000) * speedValue;
  rightSteeringValue = (rightSteeringValue/1000) * speedValue;

  Serial.print(leftSteeringValue);
  Serial.print(" ");
  Serial.print(rightSteeringValue);
  Serial.print(" ");
  Serial.print(leftPolarity);
  Serial.print(" ");
  Serial.println(rightPolarity);
}
