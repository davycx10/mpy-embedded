#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "hardware/pwm.h"
#include <Keypad.h>

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
Keypad keypad = Keypad(makeKeymap(keys), rowPINS, colsPINS, ROWS, COLS);

#define TFT_CS    17
#define TFT_DC    3
#define TFT_RST   6
#define TFT_BL    2
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

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

String codeInput = "";
const String codeSecret = "1111";
unsigned long lastInputTime = 0;
const unsigned long timeout = 15000;

void setup() {
  Serial.begin(115200);
  buzzer_init();
  tft.begin();
  digitalWrite(TFT_BL, HIGH);
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  tft.println("Enter code:");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    lastInputTime = millis();
    if (key == 'C') {
      codeInput = "";
      tft.fillScreen(ILI9341_WHITE);
      tft.setCursor(10, 10);
      tft.println("Enter code:");
    } else {
      codeInput += key;
      tft.setCursor(10, 40);
      tft.print("*"); // print * for input user
      if (codeInput.length() == codeSecret.length()) {
        tft.setCursor(10, 70);
        if (codeInput == codeSecret) {
          tft.println("Good code!");
          bip();
        } else {
          tft.println("Wrong code!");
        }
        delay(2000);
        codeInput = "";
        tft.fillScreen(ILI9341_WHITE);
        tft.setCursor(10, 10);
        tft.println("Enter code:");
      }
    }
  }
  if (codeInput.length() > 0 && (millis() - lastInputTime) > timeout) {
    codeInput = "";
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Timeout - reset");
    delay(2000);
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(10, 10);
    tft.println("Enter code:");
  }
}
