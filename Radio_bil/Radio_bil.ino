int steeringPotpin = A4; //set potentiometer for steering to pin A4, will be used to control the car's left, right turn
int speedPotpin = A5; //set potentiometer for speed to A5, will be used to control the car's speed

int steeringValue = 0; //the value from potentiometer for steering, will be used to determine how much to turn either right or left
int speedValue = 0; //the value from potentiometer for speed, will be used to control the car's speed

float steeringValueRight; //the value for car's right turn
float steeringValueLeft; //the value for car's left turn

int polarityLeft; //polarity of turning left, will signal if it is turning left
int polarityRight; //polarity of turning right, will signal if it is turning right

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  pinMode(steeringPotpin, INPUT); //set potentiometer pin for steering to INPUT mode
  pinMode(speedPotpin, INPUT); //set potentiometer pin for control of speed to INPUT mode
}

void loop() {
  steeringValue = analogRead(steeringPotpin); //variable steeringValue reads the raw value of steeringPotpin
  speedValue = analogRead(speedPotpin); //variable speedValue reads the raw value of speedPotpin

  if (steeringValue <= 256){ //if steeringValue is 256 or lower then:
    steeringValueLeft = map(steeringValue, 0, 256, 255, 0); //map steeringValueLeft so the raw steeringValue of 0-256 is converted to 255-0, when steeringPot is turning from 0 to 256 then steeringValueLeft should decrease from 255 to 0 
    steeringValueRight = map(steeringValue, 0, 256, 255, 255); //map steeringValueRight so when steeringValue is between 0-256, it keeps its value at 255
  }
  else if (steeringValue <= 512){ //else if steeringValue is 512 or lower then:
    steeringValueLeft = map(steeringValue, 256, 512, 0, 255); //map steeringValueLeft so the raw steeringValue of 256-512 is converted to 0-255, when steeringPot is turning from 256 to 512 then steeringValueLeft should increase from 0 to 255 
    steeringValueRight = map(steeringValue, 256, 512, 255, 255); //map steeringValueRight so when steeringValue is between 256-512, it keeps its value at 255
  }
  else if (steeringValue <= 768){//else if steeringValue is 768 or lower then:
    steeringValueRight = map(steeringValue, 512, 768, 255, 0); //map steeringValueRight so the raw steeringValue of 512-768 is converted to 255-0, when steeringPot is turning from 512 to 768 then steeringValueRight should decrease from 255 to 0 
    steeringValueLeft = map(steeringValue, 512, 768, 255, 255); //map steeringValueLeft so when steeringValue is between 512-768, it keeps its value at 255
  }
  else if (steeringValue <= 1024){//else if steeringValue is 1023 or lower then:
    steeringValueRight = map(steeringValue, 768, 1023, 0, 255); //map steeringValueRight so the raw steeringValue of 768-1023 is converted to 0-255, when steeringPot is turning from 768 to 1023 then steeringValueRight should increase from 0 to 255 
    steeringValueLeft = map(steeringValue, 728, 1023, 255, 255); //map steeringValueLeft so when steeringValue is between 768-1023, it keeps its value at 255
  }

  if (steeringValue >= 256){ //if steeringValue is 256 or higher then:
    polarityLeft = 10; //set value of polarityLeft to 10
  }
  else {
    polarityLeft = -10; //else set polarityLeft to -10
  }

  if (steeringValue >= 768){ //if steeringValue is 768 or higher then:
    polarityRight = -10; //set value of polarityRight to -10
  }
  else {
    polarityRight = 10; //else set polarityRight to 10
  }
  
  steeringValueRight = constrain(steeringValueRight, 0, 255); //constrain steeringValueRight with a barrier between 0-255
  steeringValueLeft = constrain(steeringValueLeft, 0, 255); //constrain steeringValueLeft with a barrier between 0-255

  speedValue = map(speedValue, 0, 1023, 0, 1000); //map speedValue so the raw value of 0-1023 converts to 0-1000
  
  //both steeringValue gets divided by 1000.0 and multiplied with speedValue so both steeringValue will be affected by speed
  steeringValueLeft = (steeringValueLeft/1000.0) * speedValue; 
  steeringValueRight = (steeringValueRight/1000.0) * speedValue; 

  //print the 4 values and print blank spaces between each value. Last print should have an "ln". Placing "ln" will show the indicated value and above in serial plotter. Blank spaces is placed to avoid zigzag graph in serial plotter.
  Serial.print(steeringValueLeft);
  Serial.print(" ");
  Serial.print(steeringValueRight);
  Serial.print(" ");
  Serial.print(polarityLeft);
  Serial.print(" ");
  Serial.println(polarityRight);
  delay(10); //delay 10ms
  
}
