const int inputs = 7;  
const int outputs = 7; 
const int steps = 8;
int systemState[inputs]; // stores the systems current sensor states
int notch = 0; // step
bool restart; 
bool start; 
bool hasReset;

int inputPins[inputs] = {A0, A1, A2, A3, A4, A6, A7};
int outputPins[outputs] = {0, 3, 4, 5, 0, 10, 11};

// outputs
// 0 = NC 0
// 1 = 3 Grabber 1
// 2 = 4 Extend Grabber 1 
// 3 = 5 Send ball 1
// 4 = NC
// 5 = 10 Up
// 6 = 11 Down
int sequence[steps][outputs] = {
    {0, 0, 1, 0, 0, 0, 0}, // step 1 extend arm 
    {0, 0, 1, 1, 0, 0, 0}, // step 2 send ball whilst still having the grabber extended
    {0, 1, 0, 0, 0, 0, 0}, // step 3 retract grabber arm and close grabber
    {0, 1, 0, 0, 0, 1, 0}, // step 4 go up whilst holding the ball with the grabber arm retracted
    {0, 1, 1, 0, 0, 1, 1}, // step 5 extend arm out and lock the up down air
    {0, 0, 1, 0, 0, 1, 0}, // step 6 release ball whilst still locked
    {0, 0, 0, 0, 0, 0, 1}, // step 7 go back down
    {0, 0, 0, 0, 0, 0, 0}, // step 8 done. close all valves lock up down
};

// inputs
// inputPins[0] A0 = NC
// inputPins[1] A1 = Tower top sense
// inputPins[2] A2 = Tower bottom sense 1
// inputPins[3] A3 = Ball actuator in sense 1
// inputPins[4] A4 = Sense ball in front of grabber 1
// inputPins[5] A6 = Grabber actuator in sense 
// inputPins[6] A7 = Grabber actuator out sense 1
int verifyState[steps][inputs] = {
    {0, 0, 1, 1, 0, 1, 0}, // startup default state sensor values
    {0, 0, 1, 1, -1, 0, 1}, // after step 1
    {0, 0, 1, -1, 1, 0, 1}, // after step 2
    {0, 0, 1, -1, 1, 1, 0}, // after step 3
    {0, 1, 0, 1, 1, 1, 0}, // after step 4
    {0, 1, 0, 1, 1, 0, 1}, // after step 5
    {0, 1, 0, 1, 0, 0, 1}, // after step 6
    {0, 0, 1, 1, 0, 1, 0} // after step 7 default state sensor values
}; // correct states for the sensors after a step in sequence has been completed

void setup() {
    for (int i = 0; i < inputs; i++) {
        pinMode(inputPins[i], INPUT);
    }
    for (int i = 0; i < outputs; i++) {
        pinMode(outputPins[i], OUTPUT);
    }
    pinMode(A13, INPUT); // A13 = START
    pinMode(A14, INPUT); // A14 = restart
    pinMode(A15, INPUT_PULLUP); // A15 = Embreak
    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i < inputs; i++) { // read all sensors, store in systemState[]
        systemState[i] = digitalRead(inputPins[i]);
    }
    if (digitalRead(A14) == 1) { // reads and stores the state of the reset button
        restart = 1;
    }
    if (digitalRead(A13) == 1 && restart == 0) { // reads and stores the state of the start button, cant start again whilst a reset is in progress
        start = 1;
        delay(200);
    }

    if (digitalRead(A15) == 0) { // checks the emergency break
        start = 0; // stops the machine when running normally
        restart = 0; // allows us to stop whilst the machine is restarting
        digitalWrite(outputPins[5], 1);
        digitalWrite(outputPins[6], 1);
    } else if (restart == 1) { // code for restart
        if (digitalRead(inputPins[2]) == 1) { // if we are at the bottom
            digitalWrite(outputPins[5], 1); // lock up down
            digitalWrite(outputPins[6], 1);
            digitalWrite(outputPins[2], 1); // extend grabber
            if (digitalRead(inputPins[6]) == 1) { // if grabber arm is extended
                digitalWrite(outputPins[1], 0); // open grabber (drop the ball)
                executeStep(sequence[7]); // turn all the air off
                restart = 0; 
                notch = 0; 
                start = 0;
                hasReset = 1;
            }
        } else if (digitalRead(inputPins[6]) == 1) { // if grabber arm is in extend take it in before going down
            digitalWrite(outputPins[2], 0); // retract grabber
        } else if (digitalRead(inputPins[5]) == 1){ // if the arm is in go down
            digitalWrite(outputPins[5], 0); // go down
            digitalWrite(outputPins[6], 1);
        }
    } else if (start == 1) { // runs the machine as usual
        if (verifyStep(systemState, verifyState[notch]) == 1 && notch < steps-1) { // verifies the previous step was completed and checks if we are on the last step
            notch++; // increments step
            executeStep(sequence[notch-1]); // executes the next step
        } else if (notch == steps-1) { // if we are on the last step we want to restart
            notch = 0;
        }
    }
}

void executeStep(int dStep[]) {
    for (int o = 0; o < outputs; o++) {
        if (notch == 2 && hasReset == 1 && o == 3 && digitalRead(inputPins[4]) == 1) { // exception after having reset
            digitalWrite(outputPins[o], 0);
        } else {
            digitalWrite(outputPins[o], dStep[o]); // writes the state for each pin with regards to our desired step
        }
    }
}

bool verifyStep(int cState[], int cStep[]) { // takes in the current step and the current system state and returns 1 or 0 based on wheter its completed
    int correctStates = 0; // stores the number of correct states
    for (int i = 0; i < inputs; i++) { // compares system sensor states to the expected sensor states
        if (cStep[i] == -1) { // -1 is our "dont care" indication so if the state of a sensor isnt important we put -1 in the truth table so it is ignored
            correctStates++;
        } else if (cState[i] == cStep[i]) {
            correctStates++;
        }

    }
    if (correctStates == inputs) { // checks if all the states are correct
        return 1;
    } else {
        return 0;
    }
}
