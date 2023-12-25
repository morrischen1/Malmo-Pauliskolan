
#include "config.h"

/************************ Example Starts Here *******************************/

// digital pin 5
#define BUTTON_PIN 5

// button state
bool current = false;
bool last = false;

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("digital");

int buttonState;

void setup() {

  // set button pin as an input
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  buttonState=digitalRead(BUTTON_PIN);
  io.run();

  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  if(buttonState == 0)
    current = true;
  else
    current = false;

  // return if the value hasn't changed
  if(current == last)
    return;

  // save the current state to the 'digital' feed on adafruit io
  Serial.print("sending button -> ");
  Serial.println(current);
  digital->save(current);

  // store last button state
  last = current;

}
