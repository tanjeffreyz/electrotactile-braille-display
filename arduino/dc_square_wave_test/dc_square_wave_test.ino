int frequency = 1000;   //Frequency in Hz
double dutyCycle = 0.50;   //Duty cycle as a fraction

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
  digitalWrite(10, HIGH);
  delayMicroseconds(timeHigh);
  digitalWrite(10, LOW);
  delayMicroseconds(timeLow);
}
