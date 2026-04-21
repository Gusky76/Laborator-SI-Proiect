#include <stdint.h>
#include "servocontrol.h"
#include "drivers/adc/adc.h"
#include "drivers/pwm/pwm.h"
#include "drivers/gpio/gpio.h"

#define SERVO_PORT GPIO_PORTB
#define SERVO_PIN  1

#define POT_CHANNEL 0

void ServoControl_Init(void)
{
    ADC_Init();

    GPIO_Init(SERVO_PORT, SERVO_PIN, GPIO_OUTPUT);
    PWM_Init(SERVO_PORT, SERVO_PIN, 50);
}

void ServoControl_Update(void)
{
    uint16_t adc_value;
    uint8_t duty;

    adc_value = ADC_Read(POT_CHANNEL);

    duty = 13 + ((adc_value * (26 - 13)) / 1023);

    PWM_SetDutyCycle(SERVO_PORT, SERVO_PIN, duty);
}