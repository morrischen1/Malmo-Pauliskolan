
#include "config.h"

/************************ Example Starts Here *******************************/

// analog pin 0
#define BATTERY_PIN A13

// photocell state
float voltage = 0;
int last = -1;

// set up the 'analog1.0' feed
AdafruitIO_Feed *analog = io.feed("analog1.0");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  //while(! Serial);

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

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the voltage state of the photocell
  voltage = analogRead(BATTERY_PIN);
  voltage = voltage*3.3*2.0*1.1/4096.0;

  // return if the value hasn't changed
  if(voltage == last)
    return;

  // save the voltage state to the analog feed
  Serial.print("sending -> ");
  Serial.println(voltage);
  //float x = ((voltage*3.3*2.0*1.1)/4096.0);
  //Serial.println(x);
  analog->save(voltage);
  //analog->save(x);

  // store last photocell state
  //last = voltage;

  // wait three seconds (1000 milliseconds == 1 second)
  //
  // because there are no active subscriptions, we can use delay()
  // instead of tracking millis()
  delay(3000);
}
