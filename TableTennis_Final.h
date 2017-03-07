#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// Hardware SPI connection
MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);
// Arbitrary output pins
// MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

int N_Score; 
int S_Score; 
String hash;
const int buttonN_Pin = 6; 
const int buttonS_Pin = 7; 
const int buttonResetPin = 8; 
int buttonState = 0;
int target_score = 15;

void setup() {
  P.begin();
  setupScreen();  
  pinMode(buttonN_Pin, INPUT);

}

void setupScreen() 
{ 
  P.displayReset(); 
  N_Score = 0; 
  S_Score = 0; 
  hash = " - ";
  P.print(N_Score + hash + S_Score);
}

void loop() {
  P.displayAnimate();
    digitalWrite(buttonN_Pin, HIGH);
    digitalWrite(buttonS_Pin, HIGH);
    digitalWrite(buttonResetPin, HIGH);
    buttonState = digitalRead(buttonN_Pin); 
  if(buttonState == LOW) 
  { 
    N_Score++; 
    P.print(N_Score + hash + S_Score);
    delay(1000); 
  } 
    buttonState = digitalRead(buttonS_Pin); 
  if(buttonState == LOW) 
  { 
    S_Score++;
    P.print(N_Score + hash + S_Score);
    delay(1000); 
  }
   buttonState = digitalRead(buttonResetPin);
  if(buttonState == LOW) 
  { 
    setupScreen(); 
  } 

  serve_brain();
}

void serve_brain()
{
  digitalWrite(buttonResetPin, HIGH);
  if ((N_Score == S_Score) && (S_Score >= (target_score-1)))
  {
    P.displayReset();
    P.print("DEUCE");
  }
  if ((S_Score == (N_Score+1)) && (N_Score >= (target_score-1)))
  {
    P.displayReset();
    P.print("ADV >");
  }
  if ((N_Score == (S_Score+1)) && (S_Score >= (target_score-1)))
  {
    P.displayReset();
    P.print("< ADV");
   }
  if ((N_Score >= target_score)&&(N_Score >= (S_Score + 2)))
  {
       buttonState = digitalRead(buttonResetPin);
    if(buttonState == LOW) 
      { 
        setupScreen(); 
      } 
    else
      {
        P.displayReset();
        P.print("NORTH");
        delay(1000); 
        P.displayClear();
        P.print("WINS");
        delay(1000);           
      }
  }
    if ((S_Score >= target_score)&&(S_Score >= (N_Score + 2)))
  {
       buttonState = digitalRead(buttonResetPin);
    if(buttonState == LOW) 
      { 
        setupScreen(); 
      } 
    else
      {
        P.displayReset();
        P.print("SOUTH");
        delay(1000); 
        P.displayClear();
        P.print("WINS");
        delay(1000);           
      }
  }
}
