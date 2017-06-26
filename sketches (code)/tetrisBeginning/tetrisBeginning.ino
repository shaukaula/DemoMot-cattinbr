//Librairies
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9340.h"
#include <SPI.h>

//Déclarations
#define CS  10
#define DC  9
#define RESET 8

Adafruit_ILI9340 tft = Adafruit_ILI9340(CS, DC, RESET);

//const int buttonsPin = 48;
const int PINSWITCH = 44;
const int MAXHEIGHT = 17;
const int MAXWIDTH = 10;
const int SQUARESIZE = 18;
const int COORDINATES = 2;
int tglState, lastTglState, gameTable[MAXHEIGHT][MAXWIDTH], score, level, lines, anaNumber, randomPiece;
volatile int interruptPin = 2;

void setup()
{
  Serial.begin(9600);
  Serial.println("Start...");

  anaNumber = analogRead(0);
  lastTglState = 1;
  score = 0;
  level = 1;
  lines = 0;

  //pinMode(buttonsPin, INPUT_PULLUP);
  pinMode(PINSWITCH, INPUT);
  randomSeed(anaNumber);
  attachInterrupt(digitalPinToInterrupt(interruptPin), startGame_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin), pauseGame_ISR, CHANGE);

  tft.begin();
  tft.setRotation(0);
  tft.setTextSize(6);
  tft.setCursor(5, 25);
  tft.setTextColor(ILI9340_BLACK);
  tft.println("Toggle");
  tft.setCursor(5, 75);
  tft.println("to");
  tft.setCursor(5, 125);
  tft.println("play");
  tft.setCursor(5, 190);
  tft.println("Tetris");
  tft.setCursor(5, 250);
  tft.println(":-)");
}

void loop()
{
  //  int reads = digitalRead(buttonsPin);
  //  Serial.println(String(reads));
  //  delay(2000);

  tglState = digitalRead(PINSWITCH);

  if (tglState != lastTglState)
  {
    if (tglState == LOW)
    {
      //Initilisation du tableau de jeu à 0 avec deux boucles for car le tableau est multidimensionnel;
      for (int h = 0; h <= MAXHEIGHT; h++)
      {
        for (int g = 0; g <= MAXWIDTH; g++)
        {
          gameTable[h][g] = 0;
        }
      }

      //Coordonnées du "milieu" pour le spawn des objets
      int baseCoordinates[COORDINATES] = {72, 14};

      gameSetup();

      randomPiece = random(1, 8);

      switch (randomPiece)
      {
        case 1:
          tft.fillRect(baseCoordinates[0], baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_MAGENTA);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_MAGENTA);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18 * 2, SQUARESIZE, SQUARESIZE, ILI9340_MAGENTA);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18 * 3, SQUARESIZE, SQUARESIZE, ILI9340_MAGENTA);
          break;
        case 2:
          tft.fillRect(baseCoordinates[0], baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_CYAN);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_CYAN);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_CYAN);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_CYAN);
          break;
        case 3:
          tft.fillRect(baseCoordinates[0], baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_RED);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_RED);
          tft.fillRect(baseCoordinates[0] + 18 * 2, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_RED);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_RED);
          break;
        case 4:
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
          tft.fillRect(baseCoordinates[0] - 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
          break;
        case 5:
          tft.fillRect(baseCoordinates[0] - 18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);
          tft.fillRect(baseCoordinates[0] - 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);
          break;
        case 6:
          tft.fillRect(baseCoordinates[0], baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
          tft.fillRect(baseCoordinates[0] - 18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
          break;
        case 7:
          tft.fillRect(baseCoordinates[0], baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_BLACK);
          tft.fillRect(baseCoordinates[0] + 18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_BLACK);
          tft.fillRect(baseCoordinates[0], baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_BLACK);
          tft.fillRect(baseCoordinates[0] - 18, baseCoordinates[1] + 18, SQUARESIZE, SQUARESIZE, ILI9340_BLACK);
          break;
      }

      //TEST
      tft.fillRect(0, 220, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
      tft.fillRect(18, 220, SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
      tft.fillRect(36, 220, SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);
      tft.fillRect(54, 220, SQUARESIZE, SQUARESIZE, ILI9340_BLACK);
      tft.fillRect(72, 220, SQUARESIZE, SQUARESIZE, ILI9340_MAGENTA);
      tft.fillRect(90, 220, SQUARESIZE, SQUARESIZE, ILI9340_CYAN);
      tft.fillRect(108, 220, SQUARESIZE, SQUARESIZE, ILI9340_RED);
      tft.fillRect(126, 220, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
      tft.fillRect(144, 220, SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
      tft.fillRect(162, 220, SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);

    }
    else
    {
      tft.begin();
      tft.fillScreen(ILI9340_WHITE);
      tft.setCursor(105, 140);
      tft.println("PAUSE");
    }
  }
  lastTglState = tglState;
}

void gameSetup()
{
  tft.begin();
  tft.setRotation(0);
  tft.setTextSize(1);
  tft.setTextColor(ILI9340_BLACK);
  tft.fillScreen(ILI9340_GREEN);
  tft.drawFastVLine(185, 0, 320, ILI9340_BLACK);
  tft.drawFastVLine(180, 0, 320, ILI9340_BLACK);
  tft.setCursor(190, 5);
  tft.println("SCORE :");
  tft.setCursor(190, 25);
  tft.println(score);
  tft.setCursor(190, 65);
  tft.println("LEVEL :");
  tft.setCursor(190, 85);
  tft.println(level);
  tft.setCursor(190, 125);
  tft.println("LINES :");
  //tft.setCursor(190, 145);
  //tft.println(lines);
  tft.setCursor(190, 185);
  tft.println("NEXT  :");
}

void pauseGame_ISR()
{
  tft.begin();
  tft.fillScreen(ILI9340_WHITE);
  tft.setCursor(105, 140);
  tft.println("PAUSE");
}

void startGame_ISR()
{
  
}

