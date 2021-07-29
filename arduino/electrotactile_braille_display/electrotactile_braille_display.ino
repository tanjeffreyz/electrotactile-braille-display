/////////////////////
//    Variables    //
/////////////////////
const int timerFrequency = 20000;
const double timerPeriod = 1.0 / timerFrequency;

// RC circuit
const int frequencyRC = 1000;
double dutyCycleRC = 0.15;
double counterRC = 0.0;
boolean toggleRC = 0;   //0 = Low, 1 = High

// Transformer MOSFET
const int frequencySW = 200;
const double dutyCycleSW = 0.3;
double counterSW = 0.0;
boolean toggleSW = 0;   //0 = Low, 1 = High

// Feedback control
const double targetVoltage = 2.00;
const double kRC = 1.045;   // Scales the counter increments to counter period distortion. This was experimentally determined.
const double kP = 0.001;
const double kI = 0.0003;
double accumulatedError = 0.0;
const double kD = 0.0001;
double prevError = 0.0;


/////////////////////
//    Functions    //
/////////////////////
void setup() {
  pinMode(10, OUTPUT);    // Supplies voltage to transformer
  pinMode(9, OUTPUT);     // Square wave to activate transformer
  
  Serial.begin(1000000);
  
  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 799;   // Compare match register = 16*10^6 / 20000 - 1 for a frequency of 20k Hz
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  counterRC += (timerPeriod * kRC);   // Increment = 1 / (frequency of timer) = 1 / 20000 = 0.00005
  counterSW += 0.00005;
}


void loop() {
  interrupts();

  // RC Signal
  if ((toggleRC) && (counterRC >= (1.0 - dutyCycleRC) / (double)frequencyRC)) {   //this waits for a period of time (time low) before turning the signal high, hence the (1.0 - dutyCycle) factor
    digitalWrite(10, HIGH);
    //Serial.println("High");
    counterRC = 0.0;
    toggleRC = 0;
  } else if ((!toggleRC) && (counterRC >= dutyCycleRC / (double)frequencyRC)) {   //this waits for a period of time (time high) before turning the signal low, hence the (dutyCycleRC) factor
    digitalWrite(10, LOW);
    //Serial.println("Low");
    counterRC = 0.0;
    toggleRC = 1;
  }

  // Square wave for transformer MOSFET
  if (toggleSW && counterSW >= (1.0 - dutyCycleSW) / (double)frequencySW) {   //this waits for a period of time (time low) before turning the signal high, hence the (1.0 - dutyCycle) factor
    digitalWrite(9, HIGH);
    counterSW = 0.0;
    toggleSW = 0;
  } else if (!toggleSW && counterSW >= dutyCycleSW / (double)frequencySW) {   //this waits for a period of time (time high) before turning the signal low, hence the (dutyCycleRC) factor
    digitalWrite(9, LOW);
    counterSW = 0.0;
    toggleSW = 1;
  }
 
  // Regulate output voltage
  int reading = analogRead(A6);
  if (reading >= 100) {   // Only regulate while finger is on the pad
    double currVoltage = reading / 1023.0;
    double currError = targetVoltage - currVoltage;
    accumulatedError += currError * timerPeriod;
    dutyCycleRC += kP * currError + kI * accumulatedError + kD * (currError - prevError);    // PID feedback control
    prevError = currError;
  } else {
    dutyCycleRC = 0.00;
  }

  // Cap the dutycycle
  if(dutyCycleRC >= 1.00) {
    dutyCycleRC = 1.00;
  } else if(dutyCycleRC <= 0.00) {
    dutyCycleRC = 0.00;
  }
}
