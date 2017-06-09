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
const int MAXPIECESIZE = 4;
const int SQUARESIZE = 18;
const int COORDINATES = 2;
int tglState, lastTglState, gameTable[MAXHEIGHT][MAXWIDTH];

void setup()
{
  Serial.begin(9600);
  Serial.println("Start...");

  lastTglState = 1;

  //pinMode(buttonsPin, INPUT_PULLUP);
  pinMode(PINSWITCH, INPUT);

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

      int i[MAXPIECESIZE][MAXPIECESIZE] = {1, 0, 0, 0,
                                           1, 0, 0, 0,
                                           1, 0, 0, 0,
                                           1, 0, 0, 0
                                          };
      int t[MAXPIECESIZE][MAXPIECESIZE] = {1, 1, 1, 0,
                                           0, 1, 0, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0
                                          };
      int o[MAXPIECESIZE][MAXPIECESIZE] = {1, 1, 0, 0,
                                           1, 1, 0, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0
                                          };
      int j[MAXPIECESIZE][MAXPIECESIZE] = {1, 1, 0, 0,
                                           1, 0, 0, 0,
                                           1, 0, 0, 0,
                                           0, 0, 0, 0
                                          };
      int l[MAXPIECESIZE][MAXPIECESIZE] = {1, 1, 1, 0,
                                           1, 0, 0, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0
                                          };
      int z[MAXPIECESIZE][MAXPIECESIZE] = {1, 1, 0, 0,
                                           0, 1, 1, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0
                                          };
      int s[MAXPIECESIZE][MAXPIECESIZE] = {0, 1, 1, 0,
                                           1, 1, 0, 0,
                                           0, 0, 0, 0,
                                           0, 0, 0, 0
                                          };

      tft.begin();
      tft.setRotation(0);
      tft.setTextSize(1);
      tft.setTextColor(ILI9340_BLACK);
      tft.fillScreen(ILI9340_GREEN);
      tft.drawFastVLine(185, 0, 320, ILI9340_BLACK);
      tft.drawFastVLine(180, 0, 320, ILI9340_BLACK);
      tft.setCursor(190, 5);
      tft.println("SCORE :");
      tft.setCursor(190, 65);
      tft.println("LEVEL :");
      tft.setCursor(190, 125);
      tft.println("LINES :");
      tft.setCursor(190, 185);
      tft.println("NEXT  :");

      //Coordonnées du milieu pour le spawn des objets
      int baseCoordinates[COORDINATES] = {81,14};
      
      for (int h = 0; h <= MAXPIECESIZE; h++)
      {
        for (int g = 0; g <= MAXPIECESIZE; g++)
        {
          if (t[h][g] == 1)
          {
            tft.fillRect(baseCoordinates[0], baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
            t[h][g] = 2;
          }
          else if (t[h-1][g] != NULL && t[h-1][g] == 2)
          {
            tft.fillRect(baseCoordinates[0]-18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
            t[h-1][g] = 2;
          }
          else if (t[h+1][g] != NULL && t[h+1][g] == 2)
          {
            tft.fillRect(baseCoordinates[0]+18, baseCoordinates[1], SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
            t[h+1][g] = 2;
          }
          else if (t[h][g+1] != NULL && t[h][g+1] == 2)
          {
            tft.fillRect(baseCoordinates[0], baseCoordinates[1]+18, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
            t[h][g+1] = 2;
          }
          else if (t[h][g-1] != NULL && t[h][g-1] == 2)
          {
            tft.fillRect(baseCoordinates[0], baseCoordinates[1]-18, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
            t[h][g-1] = 2;
          }
        }
      }

      tft.fillRect(0, 120, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
      tft.fillRect(18, 120, SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
      tft.fillRect(36, 120, SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);
      tft.fillRect(54, 120, SQUARESIZE, SQUARESIZE, ILI9340_BLACK);
      tft.fillRect(72, 120, SQUARESIZE, SQUARESIZE, ILI9340_MAGENTA);
      tft.fillRect(90, 120, SQUARESIZE, SQUARESIZE, ILI9340_CYAN);
      tft.fillRect(108, 120, SQUARESIZE, SQUARESIZE, ILI9340_RED);
      tft.fillRect(126, 120, SQUARESIZE, SQUARESIZE, ILI9340_BLUE);
      tft.fillRect(144, 120, SQUARESIZE, SQUARESIZE, ILI9340_WHITE);
      tft.fillRect(162, 120, SQUARESIZE, SQUARESIZE, ILI9340_YELLOW);
      
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
