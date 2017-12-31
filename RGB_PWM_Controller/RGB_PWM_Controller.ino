//#include <Keypad.h>


double timeInc = 0.01;
int cP = 1;
double currentTime = 0.0;
double totalTime = 10.0;

double patterns[6][8][4] = {
  {{0,0,0,.4},{255,0,0,.5},{0,0,0,.6},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}},//red flash
  {{148,0,211,.714},{75,0,130,2.14},{0,0,255,3.57},{0,255,0,5},{255,255,0,6.42},{255,127,0,7.85},{255,0,0,9.28},{-1,-1,-1,-1}},//full rainbow
  {{0,255,0,0},{0,0,255,.5},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}}, //green and blue
  {{0,255,255,0},{255,0,255,.333},{255,255,0,.666},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}},  //cyan magenta, yellow
  {{50,50,255,0},{255,255,255,.5},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}},//sky blue to white
  {{255,20,147,0},{0,191,255,.5},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}} //pink blue
};

// Define the Keymap
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[4] = { 24, 25, 26, 27 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[4] = { 32, 33, 34, 35 }; 

//Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );

int pC = 0, nC = 0;
double percentIntervalPassed = 0.0;
int curR = 0, curG = 0, curB = 0;

double shiftDuration;
double shiftPassed;


int lastColor;
int getLastColor(){
  lastColor = 0;
  while( patterns[cP][lastColor+1][3] != -1 ) lastColor++;
  //Serial.print("returning the last value of: ");
  //Serial.print(lastColor);
  return lastColor;
}


void updateColors() {
  pC = 0; 
  if ( currentTime < patterns[cP][0][3] ) { //if the time is less than the first sequential color, the prevColor is the lastColor
    pC = getLastColor(); 
  }
  while (patterns[cP][pC+1][3] != -1 && currentTime > patterns[cP][pC+1][3]) pC++; //wont execute on last color, finds prevColor by currentTime coparison
  
  if ( patterns[cP][pC+1][3] == -1 ){
    nC = 0;
    //percentIntervalPassed = (currentTime - patterns[cP][pC][3] >= 0 ? currentTime - patterns[cP][pC][3] : currentTime - patterns[cP][pC][3] + 10.0)/(patterns[cP][nC][3] + (10.0 - patterns[cP][pC][3]));
    shiftDuration = 10.0 - patterns[cP][pC][3] + patterns[cP][nC][3];
    currentTime > patterns[cP][nC][3] ? shiftPassed = currentTime - patterns[cP][pC][3] : shiftPassed = 10.0 - patterns[cP][pC][3] + currentTime;
    percentIntervalPassed = shiftPassed/shiftDuration;
  }
  else {
    nC = pC+1;    
    percentIntervalPassed = (currentTime - patterns[cP][pC][3])/(patterns[cP][nC][3] - patterns[cP][pC][3]);
  }
  
  curR = patterns[cP][pC][0] + (patterns[cP][nC][0] - patterns[cP][pC][0])*percentIntervalPassed;
  curG = patterns[cP][pC][1] + (patterns[cP][nC][1] - patterns[cP][pC][1])*percentIntervalPassed;
  curB = patterns[cP][pC][2] + (patterns[cP][nC][2] - patterns[cP][pC][2])*percentIntervalPassed; 

  //Serial.print("Time: ");
  //Serial.print(currentTime);
  //Serial.print("PIP: ");
  //Serial.print(percentIntervalPassed);
  Serial.print("Red: ");
  Serial.print(curR);
  Serial.print(", Green: ");
  Serial.print(curG);
  Serial.print(", Blue: ");
  Serial.println(curR);
  //Serial.print("PrevColor: ");
  //Serial.println(pC);
 }


void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  currentTime = 0;
}

void loop() {
  //Serial.println(kpd.getKey())
  currentTime += timeInc;
  if ( currentTime > totalTime ) currentTime -= totalTime;


  
  updateColors();
  delay(10);

  

}
