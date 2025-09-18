#include "pico/stdlib.h"

int main() {
    // Initialiser la LED interne (GPIO 25)
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);  // Allumer la LED
        sleep_ms(500);         // Attendre 500 ms
        gpio_put(LED_PIN, 0);  // Éteindre la LED
        sleep_ms(500);         // Attendre 500 ms
    }

    return 0;
}
