#include "hardware/pwm.h"

#define ROWS 4
#define COLS 4

int row_pins[ROWS] = {2, 3, 4, 5}; 
int col_pins[COLS] = {6, 7, 8, 9}; 

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

void keypad_init() {
    for (int i = 0; i < ROWS; i++) {
        pinMode(row_pins[i], OUTPUT);
        digitalWrite(row_pins[i], LOW);  // Important : mettre à 0 par défaut
    }
    for (int i = 0; i < COLS; i++) {
        pinMode(col_pins[i], INPUT_PULLDOWN);
    }
}

char keypad_get_key() {
    for (int r = 0; r < ROWS; r++) {
        for (int i = 0; i < ROWS; i++)
            digitalWrite(row_pins[i], i == r ? HIGH : LOW);

        delayMicroseconds(5);

        for (int c = 0; c < COLS; c++) {
            if (digitalRead(col_pins[c])) {
                return keys[r][c];
            }
        }
    }
    return 0;
}

char last_key = 0;

void setup() {
    Serial.begin(115200);
    keypad_init();
    buzzer_init();
}

void loop() {
    char key = keypad_get_key();

    // Détection de front montant (nouvelle touche appuyée)
    if (key != 0 && key != last_key) {
        Serial.print("Touche appuyée : ");
        Serial.println(key);

        buzzer_play_tone(440, 100);  // Bip court
    }

    last_key = key;
    delay(50); // petit délai pour limiter les fausses lectures
}