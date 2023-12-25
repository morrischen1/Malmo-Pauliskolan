//Plocka boll höj tornet, lägg tillbaka den.
int State = 0;
const int N_O_INPUTS=7+1;//0 not used
const int N_O_OUTPUTS=9+1;//0 not used
int Spins[N_O_INPUTS] = {A0, A1, A2, A3, A4, A5, A6, A7, }; //START=A13, RESET=A14, Embreak=A15, off button=38
int S[N_O_INPUTS] = {0, 0, 0, 0, 0, 0, 0, 0};
int Ypins[N_O_OUTPUTS] = {0, 5, 6, 7, 8,0,0,0,9, 10};
int Y[N_O_OUTPUTS] = {0, 0, 0, 0, 0, 0,0,0,1,1};
int emBreak=1; //active low, the emergency break will stop all actions, requiring a Reset to get going again

int Safe=0;

void setup() {
  for (int i = 0; i < N_O_INPUTS; i++) {
    pinMode(Spins[i], INPUT);
  }
  for (int i = 0; i < N_O_OUTPUTS; i++) {
    pinMode(Ypins[i], OUTPUT);
  }
  Serial.begin(115200);
}

void loop() {
  // Read all sensors, and START and RESET buttons. Special treatment for material sensors and
  //Embreak, that need to store its reading, therefore only read if nulled. Note Embreak 
  //is active low, so only store new value in emBreak when it changes from 1 to 0.
  Serial.print(Safe);
  Serial.print(" <- Safe \t S:");
  for (int i = 1; i < N_O_INPUTS; i++) {//read all sensors, store in S[]
      S[i] = digitalRead(Spins[i]);
      Serial.print(S[i]);
      Serial.print(" ");  
  }//all sensors and buttons (except "On") read
if(Safe==0){//First reset machine
Y[1]=0;
Y[2]=0;
Y[3]=0;
Y[8]=0;
Y[9]=1;
if(S[1]==0&&S[2]==1&&S[3]==1&&S[4]==0&&S[7]==1&&S[6]==0){//Reach reset pos.
  Safe=1;
  State=0;
  Serial.print("RESET finish");
}
}

if( Safe==1&&State==0&&S[2]==1&&Y[1]==0){//we are in reset position, start
  Y[2]=1;//Grabber forward
  State=1; 
}
