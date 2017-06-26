// déclaration
int pinLed1, pinLed2, pinLed3; //variables des pins
void setup()
{
  //initialisation des variables
  pinLed1 = 2;
  pinLed2 = 4;
  pinLed3 = 6;
  //initialisation des modes
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  //mise à 0V de chaque pin
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);
}
void loop()
{
    //allumage des trois LED durant 1 seconde
    digitalWrite(pinLed3,HIGH);
    digitalWrite(pinLed2,HIGH);
    digitalWrite(pinLed1,HIGH);
    delay(1000);
    //on les éteint toutes brièvement
    digitalWrite(pinLed3, LOW);
    digitalWrite(pinLed2, LOW);
    digitalWrite(pinLed1, LOW);
    delay(100);
  //Boucle de la variable temps qui diminue
  for (int temps = 1000; temps >= 200; temps -= 200)
  {
    //les trois LEDs sont éteintes
    digitalWrite(pinLed1, HIGH);//allumage LED 3
    delay(temps); // pendant la valeur de temps
    digitalWrite(pinLed1,LOW); //on éteint la 3
    delay(temps); // court délai, tout est éteint
    digitalWrite(pinLed2, HIGH);//allumage LED 2
    delay(temps); // pendant la valeur de temps
    digitalWrite(pinLed2,LOW); //on éteint la 2
    delay(temps);
    digitalWrite(pinLed3, HIGH);//allumage de LED 1
    delay(temps); // pendant la valeur de temps
    digitalWrite(pinLed3, LOW); // on éteint 1
    delay(temps);
    //la boucle reprend
  }
  //retour au début de la loop();
}

