int LEDPins [7] = {2,3,4,5,6,7,8}; //Pins for 7-segment display, in a array
int digits [10][7]={{1,1,1,1,1,1,0},//tal 0
                    {0,1,1,0,0,0,0}, //tal 1
                    {1,1,0,1,1,0,1}, //tal 2
                    {1,1,1,1,0,0,1}, //tal 3
                    {0,1,1,0,0,1,1}, //tal 4
                    {1,0,1,1,0,1,1}, //tal 5
                    {1,0,1,1,1,1,1}, //tal 6
                    {1,1,1,0,0,0,0}, //tal 7
                    {1,1,1,1,1,1,1}, //tal 8
                    {1,1,1,1,0,1,1}}; //tal 9
                    
const int buttonStartPin = 9; //Pin for start button
const int buttonStopPin = 10; //Pin for stop button
int buttonStartState; //State of start button (1 or 0)
int buttonStopState; //State of stop button (1 or 0)
bool TimerOnOff = 0; //Variable for timer to either run or stop at current number (1 or 0)
unsigned long currentMillis = 0; //The current value of millis
unsigned long previousMillis = 0; //the previous value of millis
int digit = 0; //variable to track what number shows up, its value will be max 10

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  pinMode(buttonStartPin, INPUT_PULLUP); //set buttonStartPin as INPUT_PULLUP mode
  pinMode(buttonStopPin, INPUT_PULLUP); //set buttonStopPin as INPUT_PULLUP mode
  currentMillis = millis(); //set currentMillis as millis() (time)
  //for loop assigns the LEDs as OUTPUT mode
  for(int i=0; i<7; i++){
    pinMode(LEDPins[i], OUTPUT);
  }
}

void loop() {
  buttonStartState = digitalRead(buttonStartPin); //buttonStartState digtialreads buttonStartPin
  buttonStopState = digitalRead(buttonStopPin); //buttonStopState digtialreads buttonStopPin
  currentMillis = millis(); //set currentMillis as millis() (time)

  //if Startbutton is pressed and timer is not running then it will turn on the timer and begin counting up:
  if (buttonStartState == 0 && TimerOnOff == 0){
    TimerOnOff = 1;
  }
  //if Stopbutton is pressed and timer is running then the timer will stop running, stops at last number, will continue counting if Startbutton is pressed:
  if (buttonStopState == 0 && TimerOnOff == 1){
    TimerOnOff = 0;
  }
  //as long as timer is running, the timer will count up (from 0-9)
  if (TimerOnOff == 1 && (currentMillis - previousMillis) >= 1000) {
    digit++;
    /*if (digit == 10) {
    //  digit = 0;
    }*/ 
    //commented out code above is the same as "digit %= 10;"
    digit %= 10; //stop counting after number 9 and resets automatically
    previousMillis = millis(); //sets previousMillis as millis()
  }

  //if both Start and Stopbutton is pressed, timer resets
  if (buttonStartState == 0 && buttonStopState == 0 && TimerOnOff == 0){
    digit = 0;
  }

  //Displays the number with appropiate LEDpins
  for(int i=0;i<7;i++){
    digitalWrite(LEDPins[i],digits[digit][i]); //write appropiate value for each segment
  }
  
} 
