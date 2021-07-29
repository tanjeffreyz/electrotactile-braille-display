int frequency = 1000;   //Frequency in Hz
double dutyCycle = 0.00;   //Duty cycle as a fraction
double interval = 5.00;   //Test interval length in seconds

unsigned int timeHigh = (unsigned int)(1000000 * dutyCycle / frequency);
unsigned int timeLow = (unsigned int)(1000000 * (1.0 - dutyCycle) / frequency);

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  Serial.begin(300);

  Serial.println(timeHigh);
  Serial.println(timeLow);
}

void loop() {
  // put your main code here, to run repeatedly:  
  Serial.println(dutyCycle);
  
  for(int i = 0; i < interval * frequency; i++) {
    digitalWrite(10, HIGH);
    delayMicroseconds(timeHigh);
    digitalWrite(10, LOW);
    delayMicroseconds(timeLow);
  }

  dutyCycle += 0.05;

  if(dutyCycle > 1.02) {
    dutyCycle = 0;
  }

  timeHigh = 1000000 * dutyCycle / frequency;
  timeLow = 1000000 * (1.0 - dutyCycle) / frequency;
}
