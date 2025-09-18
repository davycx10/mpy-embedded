#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "hardware/pwm.h"
#include <Keypad.h>


#define TFT_CS    17
#define TFT_DC    3
#define TFT_RST   6
#define TFT_BL    2

const byte ROWS = 4;
const byte COLS = 4;
byte rowPINS[ROWS] = {2, 3, 4, 5};
byte colsPINS[COLS] = {6, 7, 8, 9};
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

#define BUZZER_PIN 27

void buzzer_init() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
}

void buzzer_play_tone(int freq, int duration_ms) {
    uint slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint32_t clock = 125000000;
    uint32_t wrap = clock / freq;
    pwm_set_wrap(slice, wrap);
    pwm_set_chan_level(slice, pwm_gpio_to_channel(BUZZER_PIN), wrap / 2);
    pwm_set_enabled(slice, true);
    delay(duration_ms);
    pwm_set_enabled(slice, false);
}

void bip(){
  buzzer_play_tone(440, 100);
}

// Objet global
Keypad keypad = Keypad(makeKeymap(keys), rowPINS, colsPINS, ROWS, COLS);


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // rétroéclairage allumé
  tft.begin();

  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  tft.println("clik on keyboard...");

  // Initialisation buzzer
  buzzer_init();
}

void loop() {
  char key = keypad.getKey();


  if (key) {
    // Efface l'écran
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.print("Touche appuyee : ");
    tft.setTextSize(3);
    tft.setCursor(10, 40);
    tft.print(key);

    // Message associé (exemple de mapping)
    tft.setTextSize(1);
    tft.setCursor(10, 100);
    if (key == 'A') {
      tft.print("Option A selectionnee");
    } else if (key == '1') {
      tft.print("Option 1 agai ");
    } else if (key == '2') {
      tft.print("Option 2 select");
    } else if (key == '1') {
      tft.print("option 1 select");
    } else {
      tft.print("Chiffre : ");
      tft.print(key);
    }

    // Faire bip
    bip();

    delay(500); // Petit délai pour éviter double lecture
  }
}
