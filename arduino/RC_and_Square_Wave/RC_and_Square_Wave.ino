//---------------//
//   Libraries   //
//---------------//
#include <Chrono.h>
#include <LightChrono.h>



//---------------//
//   Variables   //
//---------------//
//Variables for controlling the RC voltage:
const int frequencyRC = 1000;   //CONSTANT Frequency in Hz
double dutyCycleRC = 0.250;   //Duty cycle as a fraction (will be modified by feedback

/*
double counterRC = 0;   //Counts time elapsed in seconds. Is a double because int overflows in this application
int toggleRC = 0;   //Determines whether the pin is to be turned high or low
*/

//Variables for generating a square wave:
const int frequencySW = 1000;   //Frequency in Hz
const double dutyCycleSW = 0.30;   //Duty cycle as a fraction

/*
int counterSW = 0;   //Counts time elapsed in seconds. Is a double because int overflows in this application
int toggleSW = 0;   //Determines whether the pin is to be turned high or low
*/



//---------------//
//   Functions   //
//---------------//
void setup() {
  // put your setup code here, to run once:
  Chrono chronoRC;
  Chrono chronoSW;
  
  pinMode(10, OUTPUT);   //Pin 10 is the RC circuit pin
  pinMode(9, OUTPUT);   //Pin 9 creates the DC square wave
  Serial.begin(300);
}

void loop() {
  // put your main code here, to run repeatedly:  
  if(chronoRC.has


/*  
  //For the RC circuit:
  if((toggleRC == 0) && (counterRC >= 1.0 / frequencyRC * (1.0 - dutyCycleRC))) {   //1.0 - dutyCycleRC in the if statement for timeHigh because the if statement waits for the time UNTIL HIGH (aka time low)
    digitalWrite(10, HIGH);
    //Serial.println("high");
    counterRC = 0;
    toggleRC++;
  }
  
  if((toggleRC == 1) && (counterRC >= 1.0 / frequencyRC * (dutyCycleRC))) {
    digitalWrite(10, LOW);
    //Serial.println("low");
    counterRC = 0;
    toggleRC--;
  }

  //For the square wave:
  if((toggleSW == 0) && (counterSW >= 1 / frequencySW * 1000000 * dutyCycleSW)) {
    digitalWrite(9, HIGH);
    counterSW = 0;
    toggleSW += 1;
  }

  if((toggleSW == 1) && (counterSW >= 1 / frequencySW * 1000000 * (1.0 - dutyCycleSW))) {
    digitalWrite(9, LOW);
    counterSW = 0;
    toggleSW -= 1;
  }

  //To iterate all counters
  delayMicroseconds(10);
  counterRC += 0.00001;
  //Serial.println(counterRC);
  //counterSW++;  
*/
}
