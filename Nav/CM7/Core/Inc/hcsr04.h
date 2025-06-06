#ifndef SR04_SR04_H
#define SR04_SR04_H
#include "stm32h7xx_hal.h"
// HC-SR04 struct
typedef struct {
    GPIO_TypeDef *trig_port;  // Trigger pin port
    uint16_t trig_pin;  // Trigger pin number
    TIM_HandleTypeDef *echo_htim;  // Echo pin timer
    uint16_t echo_channel;  // Echo pin timer channel
    uint8_t capture_flag;  // Echo pin capture flag
    uint32_t start_counter;  // Counter value at rising edge
    uint32_t end_counter;  // Counter value at falling edge
    uint32_t distance;  // Distance in mm
    uint32_t last_distance;  // Last distance
    uint16_t tim_update_count;  // Timer update count
} sr04_t;

// HC-SR04 functions
void sr04_init(sr04_t *sr04_struct);
void sr04_trigger(sr04_t *sr04_struct);
void sr04_read_distance(sr04_t *sr04_struct);  // This function should be called in the timer input capture callback

#endif //SR04_SR04_H
