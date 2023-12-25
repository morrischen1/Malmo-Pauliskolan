/*
  Klo åka ut
  Bollutmataren går ut, boll skickas ut om det inte finns boll
  Bollutmataren går in, Klo greppar
  Klo åka in
  Klo åka upp
  Klo åka ut
  Klo släpper
  Klo åker in
  Klo åker ner
  
  Inputs:
  A1 = uppe sensor
  A2 = nere sensor
  A3 = bollutmatre lyser = inne, lyser inte = ute
  A4 = bollsensor
  A6 = klor bak
  A7 = klor fram

  Outputs:
  D3 = stäng, öppna klor
  D4 = ut, in
  D5 = skjuta ut boll
  D10 = åka upp
  D11 = åka ner

  Start startar
  Reset resetar till default position endast om Embreak är nedtryckt
  Embreak stoppad maskinen, reset fixar
*/

//Grab and deliver ball
int machineStep = 0;         //loop is divided in different steps, will determine which step machine is on
const int INPUTS = 15 + 1;   //0 not used, number of inputs
const int OUTPUTS = 11 + 1;  //0 not used, number of outputs

//SIP = sensor input pins
int SIP[INPUTS] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15}; //sensor pins, different combination will make a part move to complete the loop
//SOP = sensor output pins
int SOP[OUTPUTS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; //pins for output, the parts that moves
//SR = states at reset
int SR[OUTPUTS] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}; //default output values, ofr default position
//SSI = sensor state inputs
int SSI[INPUTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //state for respective input pin, will determine wether a sensor is 1 or 0

bool ON = 0;  //determines wether the loop should be running or not
int safe = 0;  //determines wether it is safe to start loop or not
int resetState = 0;  //determines where in the reset process the machine is
int emBreak = 1;  //determines if the machine is stopped

void setup() {
  Serial.begin(115200);
  //sets all pins in SIP array as INPUT mode
  for (int i = 0; i < INPUTS; i++){
    pinMode(SIP[i], INPUT);
  }
  //sets all pins in SOP array as OUTPUT mode
  for (int i = 0; i < OUTPUTS; i++){
    pinMode(SOP[i], OUTPUT);
  }
}

void loop(){

  for (int i = 0; i < INPUTS; i++){ //read all sensors, store in SSI[]
    SSI[i] = digitalRead(SIP[i]);
  }
  
  if (safe == 0 && emBreak == 1){ //if not safe and break not pressed
    if (resetState == 0 && SSI[4] == 0){
      resetState = 1; //set resetState at 1 if it was 0 and there is no ball detected
    }
    if (resetState == 1){
      for (int i = 0; i < OUTPUTS; i++){
        digitalWrite(SOP[i], SR[i]); //set all outputs as SR[] if resetState is 1
      }
      if (SSI[2] == 1 && SSI[6] == 1){ 
        for (int i = 0; i < OUTPUTS; i++){
          digitalWrite(SOP[i], 0); //set all outputs as 0 if claw is retracted and at the bottom, (reset position)
        }
        safe = 1; //safe to start loop, everything in correct default position
        resetState = 0; //resetState set to 0
      }
    }
    if (resetState == 0 && SSI[4] == 1){
      resetState = 2; //set resetState to 2 if it was on 0 and if there is a ball detected
    }
    if (resetState == 2 && SSI[2] == 0){
      digitalWrite(4, 0); //retract claw if resetState is 2 and if claw is at the bottom
      if (SSI[6] == 1) {
        for (int i = 0; i < OUTPUTS; i++){
          digitalWrite(SOP[i], SR[i]); //if claws retracted then set all outputs as SR[]
        }
        resetState = 3; 
      }
    }
    if (SSI[2] == 1 && resetState == 3){
      digitalWrite(4, 1); //extend claw if resetState is 3 and if claw is at the bottom
      if (SSI[7] == 1){
        for (int i = 0; i < OUTPUTS; i++){
          digitalWrite(SOP[i], 0); //set all outputs as 0 if claw is extended
        }
        safe = 1; 
        resetState = 0; 
      }
    }
  }

  if (SSI[15] == 0){ //if break button is pressed, stop the loop
    emBreak = 0;
    safe = 0;
    ON = 0;
    machineStep = 0;
    digitalWrite(10, 1);
    digitalWrite(11, 1);
  }
  if (SSI[14] == 1 && emBreak == 0){ //if reset button is pressed, start resetting to default position
    emBreak = 1;
    safe = 0;
    ON = 0;
    machineStep = 0;
  }
  if (safe == 1 && SSI[13] == 1){ //if start button is pressed and safe to start loop then start loop
    ON = 1;
  }

  if (safe == 1 && ON == 1){
    if (machineStep == 0){ 
      digitalWrite(4, 1); //extend claw
      if (SSI[7] == 1){ 
        machineStep = 1; //claw extended = on to the next step
      }
    }
    if (machineStep == 1){
      digitalWrite(5, 1); //next step is push ball forward, ballpusher out
      if (SSI[4] == 1){ 
        digitalWrite(3, 1); //ball detected by sensor, claw grabs
        digitalWrite(5, 0); //ballpusher in
        machineStep = 2; //claw has ball = on to the next step
      }
    }
    if (machineStep == 2){ 
      digitalWrite(4, 0); //next step is retract claw with ball
      if (SSI[6] == 1){ 
        machineStep = 3; //claw has ball and retracted = on to the next step
      }
    }
    if (machineStep == 3){ 
      digitalWrite(10, 1); //next step is move claw with ball up
      if (SSI[1] == 1){ 
        digitalWrite(11, 1);
        machineStep = 4; //claw with ball is at the top, stop going up by counter with going down = on to the next step
      }
    }
    if (machineStep == 4){ 
      digitalWrite(4, 1); //next step is extend claw with ball 
      if (SSI[7] == 1){ 
        digitalWrite(3, 0); //claw release ball
        digitalWrite(4, 0); //claw retracts
        machineStep = 5; //claw with no ball at the top = on to the next step
      }
    }
    if (machineStep == 5){ 
      digitalWrite(10, 0); //claw goes down by stop going up - no more counter
      if (SSI[2] == 1){ 
        digitalWrite(11, 0); //claw stops going down
        machineStep = 0; //loop restarts, back to step 0
      }
    }
  }
}
