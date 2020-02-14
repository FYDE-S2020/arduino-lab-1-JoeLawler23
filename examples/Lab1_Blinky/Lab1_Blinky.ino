#define LED_PIN 2

void setup() {
  // put your setup code here, to run once:
  // initialize digital pin LED_PIN as an output.
  pinMode(LED_PIN, OUTPUT);
}

void timedBlink(int interval){
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(interval);                       // wait for interval seconds
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(interval);                       // wait for interval seconds
}
void dimmer(int freq, int duty) {
  int period, onTime, offTime;
  period = 1000/freq;
  onTime = period * duty / 100;
  offTime = period - onTime;
  digitalWrite(LED_PIN, HIGH);
  delay(onTime);
  digitalWrite(LED_PIN, LOW);
  delay(offTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 100; i = i + 10){
    dimmer(100-i,i);
  }
  for(int i = 0; i < 100; i = i + 10){
    dimmer(100-i,100-i);
  }
//  timedBlink(250);
//  timedBlink(500);
//  timedBlink(1000);
}
