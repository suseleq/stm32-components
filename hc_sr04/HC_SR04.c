/*
 * HC_SR04.c
 *
 *  Created on: May 4, 2025
 *      Author: Kuba
 */

#include "HC_SR04.h"


void hc_sr04_init(hc_sr04_t *sensor, TIM_HandleTypeDef *htim_echo, TIM_HandleTypeDef *htim_trig, uint32_t trig_channel)
{
	sensor->htim_echo = htim_echo;
	sensor->htim_trig = htim_trig;
	sensor->trig_channel = trig_channel;
	sensor->echo_us = 0;
	sensor->distance_cm = 0.0f;

	HAL_TIM_IC_Start_IT(sensor->htim_echo, TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(sensor->htim_trig, sensor->trig_channel);
}

float hc_sr04_calculate_distance(hc_sr04_t *sensor)
{
    return ((float)sensor->echo_us * HC_SR04_US_TO_CM_CONVERTER);
}

void read_distance(hc_sr04_t *sensor){
	sensor->echo_us = HAL_TIM_ReadCapturedValue(sensor->htim_trig, TIM_CHANNEL_2);
	sensor->distance_cm = hc_sr04_calculate_distance(sensor);
}

