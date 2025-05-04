/*
 * HC_SR04.h
 *
 *  Created on: May 4, 2025
 *      Author: Kuba
 */

#ifndef INC_HC_SR04_H_
#define INC_HC_SR04_H_

#include "stm32f7xx_hal.h"

#define HC_SR04_US_TO_CM_CONVERTER 0.017f

typedef struct
{
    TIM_HandleTypeDef *htim_echo;
    TIM_HandleTypeDef *htim_trig;
    uint32_t trig_channel;
    float distance_cm;
    uint32_t echo_us;
} hc_sr04_t;


void hc_sr04_init(hc_sr04_t *sensor, TIM_HandleTypeDef *htim_echo, TIM_HandleTypeDef *htim_trig, uint32_t channel);

float hc_sr04_calculate_distance(hc_sr04_t *sensor);
void read_distance(hc_sr04_t *sensor);

#endif /* INC_HC_SR04_H_ */
