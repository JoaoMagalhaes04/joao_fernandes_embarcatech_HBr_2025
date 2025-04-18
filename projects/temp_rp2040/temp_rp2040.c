#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "include/ssd1306.h"

// Configuração I2C para o display OLED
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

// Constantes para conversão de temperatura
#define ADC_CONVERSAO (3.3f / (1 << 12))    // 12-bit ADC (0-4095)
#define TEMP_OFFSET 27.0f
#define TEMP_VOLT_REF 0.706f
#define TEMP_SENS 0.001721f

// Buffer para o OLED
uint8_t buffer[SSD1306_BUF_LEN];
struct render_area tela_completa = {
    .start_col = 0,
    .end_col = SSD1306_WIDTH - 1,
    .start_page = 0,
    .end_page = SSD1306_NUM_PAGES - 1
};

// Inicializa o display OLED
void iniciar_display() {
    i2c_init(i2c1, SSD1306_I2C_CLK * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    SSD1306_init();
    calc_render_area_buflen(&tela_completa);
    memset(buffer, 0, SSD1306_BUF_LEN);
    render(buffer, &tela_completa);
}

// Inicializa o sensor de temperatura interno
void iniciar_sensor_temperatura() {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);  // Canal do sensor de temperatura
}

// Realiza leitura e conversão da temperatura
float ler_temperatura_celsius() {
    uint16_t adc_valor = adc_read();
    float tensao = adc_valor * ADC_CONVERSAO;
    float temperatura = TEMP_OFFSET - (tensao - TEMP_VOLT_REF) / TEMP_SENS;
    return temperatura;
}

// Atualiza a informação no OLED
void exibir_no_display(float temperatura) {
    char linha1[24];
    char linha2[24];

    snprintf(linha1, sizeof linha1, "Temp Interna:");
    snprintf(linha2, sizeof linha2, "%.2f C", temperatura);

    memset(buffer, 0, SSD1306_BUF_LEN);
    WriteString(buffer, 0, 0, linha1);
    WriteString(buffer, 0, 24, linha2);
    render(buffer, &tela_completa);
}

int main() {
    stdio_init_all();
    iniciar_display();
    iniciar_sensor_temperatura();

    while (true) {
        float temp = ler_temperatura_celsius();
        printf("Temperatura: %.2f °C\n", temp);
        exibir_no_display(temp);
        sleep_ms(1000);
    }

    return 0;
}
