#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "include/ssd1306.h"

#define PIN_X_AXIS 26       // ADC0
#define PIN_Y_AXIS 27       // ADC1
#define PIN_BTN     22      // Botão do joystick

#define SDA_PIN     14
#define SCL_PIN     15

// Buffer para o OLED
uint8_t display_memory[SSD1306_BUF_LEN];
struct render_area area_full = {
    .start_col = 0,
    .end_col = SSD1306_WIDTH - 1,
    .start_page = 0,
    .end_page = SSD1306_NUM_PAGES - 1
};

// Inicializa o barramento I2C e o display OLED
void oled_setup() {
    i2c_init(i2c1, SSD1306_I2C_CLK * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    SSD1306_init();
    calc_render_area_buflen(&area_full);
    memset(display_memory, 0, SSD1306_BUF_LEN);
    render(display_memory, &area_full);
}

// Prepara o ADC e botão do joystick
void joystick_setup() {
    adc_init();
    adc_gpio_init(PIN_X_AXIS);
    adc_gpio_init(PIN_Y_AXIS);

    gpio_init(PIN_BTN);
    gpio_set_dir(PIN_BTN, GPIO_IN);
    gpio_pull_up(PIN_BTN);
}

// Converte GPIO para número de canal ADC e lê valor
uint16_t ler_adc(uint gpio) {
    uint canal = gpio - 26;
    adc_select_input(canal);
    return adc_read();
}

// Renderiza os dados do joystick no OLED
void mostrar_valores(uint16_t eixo_x, uint16_t eixo_y, bool botao) {
    char texto_x[20], texto_y[20], texto_btn[20];

    snprintf(texto_x, sizeof texto_x, "Eixo X: %4d", eixo_x);
    snprintf(texto_y, sizeof texto_y, "Eixo Y: %4d", eixo_y);
    snprintf(texto_btn, sizeof texto_btn, "Botao : %s", botao ? "Ativo" : "Inativo");

    memset(display_memory, 0, SSD1306_BUF_LEN);
    WriteString(display_memory, 0, 0, "Status Joystick:");
    WriteString(display_memory, 0, 16, texto_x);
    WriteString(display_memory, 0, 32, texto_y);
    WriteString(display_memory, 0, 48, texto_btn);
    render(display_memory, &area_full);
}

int main() {
    stdio_init_all();

    joystick_setup();
    oled_setup();

    while (true) {
        uint16_t pos_x = ler_adc(PIN_X_AXIS);
        uint16_t pos_y = ler_adc(PIN_Y_AXIS);
        bool pressionado = !gpio_get(PIN_BTN);

        mostrar_valores(pos_x, pos_y, pressionado);

        sleep_ms(100);  // Atualiza a cada 100 ms
    }

    return 0;
}
