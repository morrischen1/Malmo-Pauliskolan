/*
3 buttons, 1 LED
button 1 = ON/OFF LED
button 2 = LED blink fast
button 3 = LED blink slow
If LED on, button 2 and 3 can give effect
If LED off, button 2 and 3 do not do anything when pressed
*/

int OnOffButtonPin = 7; //OnOff button set at pin 7
int OnOffButtonState; //State of OnOffButton, will either be HIGH or LOW

int FastButtonPin = 6; //Button for fast blinking set at pin 6
int FastButtonState; //State of FastButton, will either be HIGH or LOW, will set false/true on FastButtonStatus
int FastButtonStatus = false; //Status of the FastButton, will determine when LED will blink fast, set at false for now

int SlowButtonPin = 5; //Button for slow blinking set at pin 5
int SlowButtonState; //State of SlowButton, will either be HIGH or LOW, will set false/true on SlowButtonStatus
int SlowButtonStatus = false; //Status of the SlowButton, will determine when LED will blink slow, set at false for now

int ledPin = 2; //LED pin set at 2
int ledState; //State of the LED, will turn on/off LED, can either be HIGH or LOW
int ledStatus = false; //Status of the LED, determines when button 2 and 3 will work, set at false for now (OFF)

//unsigned long is used for variables that hold time instead of int as the value will be too large for "int" to store
unsigned long currentMillis; //the current "time" in ms
unsigned long previousMillis; // will store the lastest time a button was updated
const long interval = 200; // interval for each button press, used for avoiding bugs

void setup() {
  pinMode(OnOffButtonPin, INPUT_PULLUP); //sets OnOffButtonPin as INPUT_PULLUP mode
  pinMode(FastButtonPin, INPUT_PULLUP); //sets FastButtonPin as INPUT_PULLUP mode
  pinMode(SlowButtonPin, INPUT_PULLUP); //sets SlowButtonPin as INPUT_PULLUP mode
  pinMode(ledPin, OUTPUT); //sets ledPin as OUTPUT mode
}

void loop() {
//INPUT:
  OnOffButtonState = digitalRead(OnOffButtonPin); //OnOffButtonState digitalreads OnOffButtonPin
  FastButtonState = digitalRead(FastButtonPin); //FastButtonState digitalreads FastButtonPin
  SlowButtonState = digitalRead(SlowButtonPin); //SlowButtonState digitalreads SlowButtonPin
  ledState = digitalRead(ledPin); //ledState digitalreads ledPin

//LOGIC:
  currentMillis = millis(); //currentMillis stores the number of ms passed since program started
  
  if (OnOffButtonState == LOW && ledStatus == true){ // if OnOffButton is pressed and LED is turned ON
    if (currentMillis - previousMillis >= interval) { // if currentMillis - previousMillis is equals or larger than interval (200)
      previousMillis = currentMillis; //set previousMillis to currentMillis
      ledState = LOW; //set ledState to LOW (LED turns OFF)
      ledStatus = false; //set ledStatus to false
      digitalWrite(ledPin, LOW); } } //turns OFF the LED
  
  else if (OnOffButtonState == LOW && ledStatus == false){ // if OnOffButton is pressed and LED is turned OFF
    if (currentMillis - previousMillis >= interval) { 
      previousMillis = currentMillis; 
      ledState = HIGH; //set ledState to HIGH (LED turns ON)
      ledStatus = true; //set ledStatus to true
      digitalWrite(ledPin, HIGH); } } //turns ON the LED

  //-----------------------------------------//
 
  if (FastButtonState == LOW && ledStatus == true){ // if FastButton is pressed and LED is turned ON
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      FastButtonStatus = true; } } //sets FastButtonStatus to true, LED will blink fast
  
  if (ledStatus == true && FastButtonStatus == true){ // if LED is turned ON and set to LED blinking fast
    ledState =! ledState; //LED will switch state, ON will be OFF and vice versa
    digitalWrite(ledPin, ledState); // display the LED's current state, either LOW or HIGH
    delay(100); } //wait 0.1s
  
  if (FastButtonStatus == true && OnOffButtonState == LOW){ // if LED is blinking fast and OnOffButton is pressed
    ledState = LOW; //turns LED OFF
    ledStatus = false; //sets LED status to false
    FastButtonStatus = false; } //Blinking fast loop for LED will stop

  //-----------------------------------------//

  if (SlowButtonState == LOW && ledStatus == true){ // if SlowButton is pressed and LED is turned ON
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      SlowButtonStatus = true; } } //sets SlowButtonStatus to true, LED will blink slow
  
  if (ledStatus == true && SlowButtonStatus == true){ // if LED is turned ON and set to LED blinking slow
    ledState =! ledState;
    digitalWrite(ledPin, ledState);
    delay(300); }
  
  if (SlowButtonStatus == true && OnOffButtonState == LOW){ // if LED is blinking slowly and OnOffButton is pressed
    ledState = LOW;
    ledStatus = false;
    SlowButtonStatus = false; } //Blinking slow loop for LED will stop
  
  //-----------------------------------------//

  if (FastButtonStatus == true && SlowButtonState == LOW){ //If LED is blinking fast and SlowButton is pressed
    FastButtonStatus = false; //LED will stop blinking fast
    SlowButtonStatus = true; } //LED will start blinking slow
  else if (SlowButtonStatus == true && FastButtonState == LOW){ //If LED is blinking Slow and FastButton is pressed
    SlowButtonStatus = false; //LED will stop blinking slow
    FastButtonStatus = true; } //LED will start blinking fast
}
