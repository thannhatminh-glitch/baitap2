#include "stm32f10x.h"

#define LED_PIN     GPIO_Pin_12
#define BUTTON_PIN  GPIO_Pin_9

void GPIO_Config(void) {
    // B?t clock cho Port A
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio;

    // LED PA12: Output Push-Pull
    gpio.GPIO_Pin = LED_PIN;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &gpio);

    // Button PA9: Input Pull-Up (không nh?n = 1, nh?n = 0)
    gpio.GPIO_Pin = BUTTON_PIN;
    gpio.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &gpio);
}

int main(void) {
    GPIO_Config();

    uint8_t lastState = 1;  // do pull-up, m?c d?nh th? = 1
    uint8_t ledState  = 0;  // 0 = t?t, 1 = b?t

    GPIO_ResetBits(GPIOA, LED_PIN); // LED ban d?u t?t

    while (1) {
        uint8_t currentState = GPIO_ReadInputDataBit(GPIOA, BUTTON_PIN);

        // B?t c?nh xu?ng: t? 1 -> 0 (nh?n nút)
        if (lastState == 1 && currentState == 0) {
            ledState = !ledState;

            if (ledState)
                GPIO_SetBits(GPIOA, LED_PIN);   // B?t LED
            else
                GPIO_ResetBits(GPIOA, LED_PIN); // T?t LED

            // Debounce ~20ms (thô)
            for (volatile int i = 0; i < 720000; i++);
        }

        lastState = currentState;
    }
}
