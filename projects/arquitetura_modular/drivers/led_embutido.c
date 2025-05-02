#include "led_embutido.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

static bool led_state = false;

void led_embutido_init(void) {
    cyw43_arch_init();
}

void led_embutido_on(void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    led_state = true;
}

void led_embutido_off(void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    led_state = false;
}

void led_embutido_toggle(void) {
    if (led_state) {
        led_embutido_off();
    } else {
        led_embutido_on();
    }
}
