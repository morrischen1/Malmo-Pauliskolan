const int photoCell = A0;
const int LEDpin = 9;

int sensorValue = 0;
int outputValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(photoCell, INPUT);
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(photoCell);
  outputValue = map(sensorValue,0,1023,0,255);
  digitalWrite(LEDpin, outputValue);

}
