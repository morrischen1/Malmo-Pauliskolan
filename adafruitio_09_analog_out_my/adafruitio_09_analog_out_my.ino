
#include "config.h"

/************************ Example Starts Here *******************************/

// this should correspond to a pin with PWM capability
#define LED_PIN 5

// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("analog");

void setup() {

  // set up led pin as an analog output
  #if defined(ARDUINO_ARCH_ESP32)
    // ESP32 pinMode()
    ledcAttachPin(LED_PIN, 1);
    ledcSetup(1, 1200, 8);
  #else
    pinMode(LED_PIN, OUTPUT);
  #endif

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'analog' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  analog->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  analog->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever an 'analog' message
// is received from Adafruit IO. it was attached to
// the analog feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int reading = data->toInt();

  Serial.print("received <- ");
  Serial.println(reading);

  
  // write the current 'reading' to the led
  #if defined(ARDUINO_ARCH_ESP32)
    ledcWrite(1, reading); // ESP32 analogWrite()
  #else
    analogWrite(LED_PIN, reading);
  #endif

}
