// déclaration
int pinLed1, pinLed2, pinLed3, pinSwitch1; //variables des pins

void setup()
{
  //initialisation des variables
  pinLed1 = 2;
  pinLed2 = 4;
  pinLed3 = 6;
  pinSwitch1 = 52;
  
  //initialisation des modes
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinSwitch1, INPUT);
  //mise à 0V de chaque pin
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);
}
void loop()
{
  int reads = digitalRead(pinSwitch1);

  if (reads == HIGH)
  {
    digitalWrite(pinLed3, HIGH);
  }
  else
  {
    digitalWrite(pinLed3, LOW);  
  }
}

