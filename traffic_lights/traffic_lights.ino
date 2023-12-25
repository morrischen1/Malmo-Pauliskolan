int ledPins[] = {2,3,4,5,6}; //array of LEDPins

int PedbuttonPin = 8; //Button for pedestrinas to click on to change traffic lights
int PedbuttonState; //The state of the Pedbutton, either 1 or 0

int start = 1; //set variable "start" to 1, 1 = (red ligth for ped. and green light for cars), 0 = (1 is not valid but LED will have their state remaining until changed)

void setup()
{
  for (int i=0; i<5; i++){ //for loops compresses pinMode for respective ledPin to one pinMode and numberize the ledPins in a new order (0-4)
    pinMode(ledPins[i], OUTPUT); //sets all ledPins as OUTPUT mode
  }
  pinMode(PedbuttonPin, INPUT_PULLUP); //sets PedbuttonPin as INPUT_PULLUP mode
}

void loop()
{
  //currentMillis = millis();
  
  PedbuttonState=digitalRead(PedbuttonPin); //PedbutonState digitalreads PedbuttonPin

  if (start == 1){ //if variable "start" equals to 1
    digitalWrite(ledPins[0], HIGH); //Red for pedestrinas at start
    digitalWrite(ledPins[4], HIGH); //Green for cars at start
    }
  
  if (PedbuttonState == 0){ //if button pressed
    start = 0; //variable "start" set to 0
    digitalWrite(ledPins[3], HIGH); //turn on yellow light (cars)
    digitalWrite(ledPins[4], LOW); //turn off green light (pedestrians)

    //if (currentMillis - previousMillis >= interval_2s){
      //previousMillis = currentMillis;
    
    delay(2000); //wait 2 seconds
    digitalWrite(ledPins[2], HIGH); //turn red light on (cars)
    digitalWrite(ledPins[3], LOW); //turn yellow light off (cars)
    delay(1000); //wait 1 second
    digitalWrite(ledPins[0], LOW); //turn red light off (predestrians)
    digitalWrite(ledPins[1], HIGH); //turn green light on (pedestrians)
    delay(3000); //wait 3 seconds
    digitalWrite(ledPins[0], HIGH); //turn red light on (pedestrians)
    digitalWrite(ledPins[1], LOW); //turn green light off (pedestrians)
    delay(1000); //wait 1 second
    digitalWrite(ledPins[3], HIGH); //turn yellow light on (cars)
    delay(1000); //wait 1 second
    digitalWrite(ledPins[2], LOW); //turn red light off (cars)
    digitalWrite(ledPins[3], LOW); //turn yellow light off (cars)
    digitalWrite(ledPins[4], HIGH); //turn green light on (cars)
    start = 1; //set variable "start" to 1 again
      //}
  }
}
