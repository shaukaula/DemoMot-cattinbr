#include <Adafruit_CC3000.h>

const int led = 13;
const int button = 59;

//One loop
void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

//Infinite loop
void loop() {
  int reads = digitalRead(button);
  digitalWrite(led, reads);
}

