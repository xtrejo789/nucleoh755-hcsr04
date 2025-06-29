#include "GPIO.h"

void GPIO_Pin_Setup(GPIO_TypeDef *Port, uint8_t pin, uint8_t mode, uint8_t otype, uint8_t speed, uint8_t pupd, uint8_t alternate_function)
{
    // Habilitar reloj del puerto
    if (Port == GPIOA) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
    else if (Port == GPIOB) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
    else if (Port == GPIOC) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
    else if (Port == GPIOD) RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN;
    else if (Port == GPIOE) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
    else if (Port == GPIOF) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOFEN;
    else if (Port == GPIOG) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOGEN;
    else if (Port == GPIOH) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOHEN;

    // Configuración de Modo
    Port->MODER &= ~(0x3 << (2 * pin));
    Port->MODER |= (mode << (2 * pin));

    // Tipo de salida
    Port->OTYPER &= ~(1 << pin);
    Port->OTYPER |= (otype << pin);

    // Velocidad
    Port->OSPEEDR &= ~(0x3 << (2 * pin));
    Port->OSPEEDR |= (speed << (2 * pin));

    // Pull-up / Pull-down
    Port->PUPDR &= ~(0x3 << (2 * pin));
    Port->PUPDR |= (pupd << (2 * pin));

    // Configuración de función alternativa si corresponde
    if (mode == GPIO_MODE_AF)
    {
        if (pin < 8)
        {
            Port->AFR[0] &= ~(0xF << (4 * pin));
            Port->AFR[0] |= (alternate_function << (4 * pin));
        }
        else
        {
            Port->AFR[1] &= ~(0xF << (4 * (pin - 8)));
            Port->AFR[1] |= (alternate_function << (4 * (pin - 8)));
        }
    }
}

void GPIO_Pin_High(GPIO_TypeDef *Port, int pin)
{
    Port->BSRR = (1 << pin);
}

void GPIO_Pin_Low(GPIO_TypeDef *Port, int pin)
{
    Port->BSRR = (1 << (pin + 16));
}

void GPIO_Interrupt_Setup(int pin, int edge_select)
{
    EXTI->IMR1 |= (1 << pin);

    switch (edge_select)
    {
        case RISING_EDGE:
            EXTI->RTSR1 |= (1 << pin);
            break;
        case FALLING_EDGE:
            EXTI->FTSR1 |= (1 << pin);
            break;
        case RISING_FALLING_EDGE:
            EXTI->RTSR1 |= (1 << pin);
            EXTI->FTSR1 |= (1 << pin);
            break;
    }
}

