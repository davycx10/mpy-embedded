#include "pico/stdlib.h"
#include <cstdio>

#define ROWS 4
#define COLS 4

int row_pins[ROWS] = {2, 3, 4, 5};   // GPIO pour les lignes
int col_pins[COLS] = {6, 7, 8, 9};   // GPIO pour les colonnes

char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

void keypad_init() {
    // Config lignes en sortie
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], true); // sortie
    }
    // Config colonnes en entrée avec pull-down
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], false); // entrée
        gpio_pull_down(col_pins[i]);
    }
}

char keypad_get_key() {
    for (int r = 0; r < ROWS; r++) {
        // Mettre ligne active
        for (int i = 0; i < ROWS; i++)
            gpio_put(row_pins[i], i == r ? 1 : 0);

        sleep_us(5); // petit délai

        for (int c = 0; c < COLS; c++) {
            if (gpio_get(col_pins[c])) {
                return keys[r][c];
            }
        }
    }
    return 0; // aucune touche
}

int main() {
    stdio_init_all();
    keypad_init();

    while (1) {
        char key = keypad_get_key();
        if (key) {
            printf("Touche: %c\n", key);
            sleep_ms(200); // anti-rebond
        }
    }
}
