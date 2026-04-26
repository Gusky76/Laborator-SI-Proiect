#include <stdint.h>
#include "servocontrol.h"
#include "drivers/adc/adc.h"
#include "drivers/pwm/pwm.h"
#include "drivers/gpio/gpio.h"

#define SERVO_PORT GPIO_PORTB
#define SERVO_PIN  1

#define LED_PORT   GPIO_PORTB
#define LED_PIN    3   

#define POT_CHANNEL 0

void ServoControl_Init(void)
{
    ADC_Init();

    GPIO_Init(SERVO_PORT, SERVO_PIN, GPIO_OUTPUT);
    PWM_Init(SERVO_PORT, SERVO_PIN, 50);

    GPIO_Init(LED_PORT, LED_PIN, GPIO_OUTPUT);
    PWM_Init(LED_PORT, LED_PIN, 500); 
}

void ServoControl_Update(void)
{
    uint16_t adc_value;
    uint8_t servo_duty;
    uint8_t led_duty;
    uint16_t distance;

    adc_value = ADC_Read(POT_CHANNEL);

    servo_duty = 13 + ((adc_value * (26 - 13)) / 1023);
    PWM_SetDutyCycle(SERVO_PORT, SERVO_PIN, servo_duty);

    distance = (adc_value > 512) ? (adc_value - 512) : (512 - adc_value);
    led_duty = (distance * 255) / 512;
    PWM_SetDutyCycle(LED_PORT, LED_PIN, led_duty);
}