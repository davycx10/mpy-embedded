#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS    17
#define TFT_DC    3
#define TFT_RST   6
#define TFT_BL    2

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // rétroéclairage allumé

  tft.begin();
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);

  const char *message = "Explorer Board OK !";
  int size = 3; // taille du texte

  int charWidth = 6;
  int charHeight = 8;
  int textLength = strlen(message);
  int textWidth = textLength * charWidth * size;
  int textHeight = charHeight * size;

  int x = (320 - textWidth) / 2;
  int y = (240 - textHeight) / 2;

  tft.setTextSize(size);
  tft.setCursor(x, y);
  tft.println(message);
}

void loop() {
  // rien à faire ici
}
