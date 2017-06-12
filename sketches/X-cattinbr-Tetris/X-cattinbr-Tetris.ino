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
int tglState, lastTglState, gameTable[MAXHEIGHT][MAXWIDTH], score, level, lines, anaNumber, randomPiece, interruptPin;
volatile int state = LOW;

//One loop
void setup()
{
  anaNumber = analogRead(0);
  lastTglState = 1;
  score = 0;
  level = 1;
  lines = 0;
  interruptPin = 3;

  pinMode(PINSWITCH, INPUT);
  randomSeed(anaNumber);
  attachInterrupt(digitalPinToInterrupt(interruptPin), startGame_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin), game_ISR, FALLING);

  startGameSetup();
}

//Infinite loop
void loop()
{
  gameSetup();
  delay(10*10*10*10);
}

void startGame_ISR ()
{
  tft.begin();
  tft.fillScreen(ILI9340_WHITE);
  tft.setCursor(105, 140);
  tft.println("PAUSE");
  state = !state;
}

void game_ISR ()
{
    
}

void startGameSetup()
{
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

