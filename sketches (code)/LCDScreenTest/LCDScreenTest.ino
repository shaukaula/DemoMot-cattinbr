//Librairies
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9340.h"
#include <SPI.h>

//Déclarations
#define CS  10
#define DC  9
#define RESET 8

Adafruit_ILI9340 tft = Adafruit_ILI9340(CS, DC, RESET);

void setup()
{
  tft.begin();
  tft.fillScreen(ILI9340_BLACK);
  tft.setRotation(0);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9340_RED);
  tft.println("Quand on n'a que l'amour");
  tft.setTextColor(0x00FF);
  tft.println("A donner en partage");
  tft.setTextColor(ILI9340_GREEN);
  tft.println("Et rien que des chansons");
  tft.setTextColor(ILI9340_WHITE);
  tft.println("Pour répondre au tambour");
  tft.setTextColor(ILI9340_CYAN);
  tft.println("Alors sans avoir rien");
  tft.setTextColor(ILI9340_BLUE);
  tft.println("Que la force d'aimer");
  tft.setTextColor(ILI9340_MAGENTA);
  tft.println("Nous avons dans les mains");
  tft.setTextColor(0xFC00);
  tft.println("Ami, le monde entier.");
}

void loop()
{
  
}

