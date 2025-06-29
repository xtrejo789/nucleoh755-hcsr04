/*
 * GPIO.h
 *
 *  Created on: Jun 29, 2025
 *      Author: ximen
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "main.h"

// Modos de configuración
#define GPIO_MODE_INPUT     0x00
#define GPIO_MODE_OUTPUT    0x01
#define GPIO_MODE_AF        0x02
#define GPIO_MODE_ANALOG    0x03

// Tipo de salida
#define GPIO_OTYPE_PP       0x00
#define GPIO_OTYPE_OD       0x01

// Velocidad
#define GPIO_SPEED_LOW      0x00
#define GPIO_SPEED_MEDIUM   0x01
#define GPIO_SPEED_HIGH     0x02
#define GPIO_SPEED_VERYHIGH 0x03

// Pull-up / Pull-down
#define GPIO_NO_PUPD        0x00
#define GPIO_PULLUP         0x01
#define GPIO_PULLDOWN       0x02

// Configuración de flanco de interrupción
#define RISING_EDGE         0
#define FALLING_EDGE        1
#define RISING_FALLING_EDGE 2

// Función nula (sin AF)
#define NONE                0

void GPIO_Pin_Setup(GPIO_TypeDef *Port, uint8_t pin, uint8_t mode, uint8_t otype, uint8_t speed, uint8_t pupd, uint8_t alternate_function);
void GPIO_Pin_High(GPIO_TypeDef *Port, int pin);
void GPIO_Pin_Low(GPIO_TypeDef *Port, int pin);
void GPIO_Interrupt_Setup(int pin, int edge_select);

#endif /* GPIO_GPIO_H_ */
