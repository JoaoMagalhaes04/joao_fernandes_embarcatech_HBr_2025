#include "Unity/src/unity.h"
#include "temperature.h"



void setUp(void) {}
void tearDown(void) {}

void test_adc_to_celsius_27_degrees(void) {
    // 0.706V → valor de ADC esperado:
    // adc_val = (0.706 / 3.3) * 4095 ≈ 876
    uint16_t adc_val = 876;
    float temperature = adc_to_celsius(adc_val);

    TEST_ASSERT_FLOAT_WITHIN(0.5, 27.0, temperature); // tolerância de 0.5°C
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_adc_to_celsius_27_degrees);
    return UNITY_END();
}
