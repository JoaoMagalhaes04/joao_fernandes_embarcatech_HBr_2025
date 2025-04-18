#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "include/ssd1306.h"

// Pinos dos botões
#define PIN_BTN_A 5
#define PIN_BTN_B 6

// Pinos I2C
#define SDA_PIN 14
#define SCL_PIN 15

// Estados globais
volatile bool flag_start_count = false;
volatile bool flag_b_pressed = false;

int contador = 0;
int cliques_b = 0;
bool em_contagem = false;

// Timer
struct repeating_timer repetidor;

// Buffer e área do display
uint8_t display_buffer[SSD1306_BUF_LEN];
struct render_area display_area = {
    .start_col = 0,
    .end_col = SSD1306_WIDTH - 1,
    .start_page = 0,
    .end_page = SSD1306_NUM_PAGES - 1
};

// Funções
void isr_botao_a(uint gpio, uint32_t events);
void isr_botao_b(uint gpio, uint32_t events);
bool temporizador_callback(struct repeating_timer *t);
void atualizar_oled();

int main() {
    stdio_init_all();

    // Inicialização do barramento I2C
    i2c_init(i2c1, SSD1306_I2C_CLK * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Iniciar display
    SSD1306_init();
    calc_render_area_buflen(&display_area);
    memset(display_buffer, 0, SSD1306_BUF_LEN);
    render(display_buffer, &display_area);

    // Configurar botões
    gpio_init(PIN_BTN_A);
    gpio_set_dir(PIN_BTN_A, GPIO_IN);
    gpio_pull_up(PIN_BTN_A);

    gpio_init(PIN_BTN_B);
    gpio_set_dir(PIN_BTN_B, GPIO_IN);
    gpio_pull_up(PIN_BTN_B);

    // Habilitar interrupções
    gpio_set_irq_enabled_with_callback(PIN_BTN_A, GPIO_IRQ_EDGE_FALL, true, &isr_botao_a);
    gpio_set_irq_enabled(PIN_BTN_B, GPIO_IRQ_EDGE_FALL, true);

    // Inicial
    contador = 0;
    cliques_b = 0;
    em_contagem = false;
    atualizar_oled();

    // Loop principal
    while (true) {
        if (flag_start_count) {
            flag_start_count = false;

            // Reiniciar contagem
            cancel_repeating_timer(&repetidor);
            contador = 9;
            cliques_b = 0;
            em_contagem = true;
            atualizar_oled();

            add_repeating_timer_ms(1000, temporizador_callback, NULL, &repetidor);
        }

        if (flag_b_pressed && em_contagem) {
            flag_b_pressed = false;
            cliques_b++;
            atualizar_oled();
        }

        tight_loop_contents();
    }

    return 0;
}

void isr_botao_a(uint gpio, uint32_t events) {
    if (gpio == PIN_BTN_A) {
        sleep_ms(30); // debounce
        if (!gpio_get(PIN_BTN_A)) {
            flag_start_count = true;
        }
    }
}

void isr_botao_b(uint gpio, uint32_t events) {
    if (gpio == PIN_BTN_B) {
        sleep_ms(30); // debounce
        if (!gpio_get(PIN_BTN_B)) {
            flag_b_pressed = true;
        }
    }
}

bool temporizador_callback(struct repeating_timer *t) {
    if (!em_contagem) return false;

    contador--;

    if (contador < 0) {
        em_contagem = false;
        return false; // encerra o timer
    }

    atualizar_oled();
    return true; // continua o timer
}

void atualizar_oled() {
    char linha_superior[20];
    char linha_inferior[20];

    memset(display_buffer, 0, SSD1306_BUF_LEN);

    sprintf(linha_superior, "Contador: %d", contador);
    sprintf(linha_inferior, "Cliques B: %d", cliques_b);

    WriteString(display_buffer, 0, 0, linha_superior);
    WriteString(display_buffer, 0, 16, linha_inferior);
    render(display_buffer, &display_area);
}