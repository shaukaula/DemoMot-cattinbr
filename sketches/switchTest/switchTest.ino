// déclaration
int pinLed1, pinLed2, pinLed3, pinSwitch1, pinSwitch2; //variables des pins

void setup()
{
  //initialisation des variables
  pinLed1 = 2;
  pinLed2 = 4;
  pinLed3 = 6;
  pinSwitch2 = 50;
  pinSwitch1 = 52;

  //initialisation des modes
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinSwitch1, INPUT);
  pinMode(pinSwitch2, INPUT);
  //mise à 0V de chaque pin
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);

  Serial.begin(9600);
  Serial.println("Starting");
}

void loop()
{
  int tgl1State = digitalRead(pinSwitch1);
  int tgl2State = digitalRead(pinSwitch2);

  if (tgl2State == LOW)
  {
    if (tgl1State == LOW)
    {
      //allumage des trois LED
      delay(100);
      digitalWrite(pinLed3, HIGH);
      delay(100);
      digitalWrite(pinLed2, HIGH);
      delay(100);
      digitalWrite(pinLed1, HIGH);
      delay(100);
      //on les éteint toutes brièvement
      digitalWrite(pinLed3, LOW);
      digitalWrite(pinLed2, LOW);
      digitalWrite(pinLed1, LOW);
      delay(1000);
    }
    else
    {
      //allumage des trois LED
      delay(100);
      digitalWrite(pinLed1, HIGH);
      delay(100);
      digitalWrite(pinLed2, HIGH);
      delay(100);
      digitalWrite(pinLed3, HIGH);
      delay(100);
      //on les éteint toutes brièvement
      digitalWrite(pinLed3, LOW);
      digitalWrite(pinLed2, LOW);
      digitalWrite(pinLed1, LOW);
      delay(1000);
    }
  }
  else
  {
      digitalWrite(pinLed3, LOW);
      digitalWrite(pinLed2, LOW);
      digitalWrite(pinLed1, LOW);
  }
}

