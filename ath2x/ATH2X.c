/*
 * ATH2X.c
 *
 *  Created on: May 5, 2025
 *      Author: Kuba
 */


#include "ATH2X.h"

HAL_StatusTypeDef  ath2x_init(ath2x_t *sensor, I2C_HandleTypeDef *hi2c){
	HAL_StatusTypeDef ret;
	sensor->adress = AHT2x_ADRESS << 1;
	sensor->hi2c = hi2c;
	sensor->humidity = 0.0f;
	sensor->temperature = 0.0f;
	HAL_DELAY(100);
	ret = HAL_I2C_Master_Transmit(sensor->hi2c, sensor->adress, GET_STATUS, 1, HAL_MAX_DELAY);
	if(ret != HAL_OK){
		return HAL_ERROR;
	}
	uint8_t status;
	ret = HAL_I2C_Master_Receive(sensor->hi2c, sensor->adress, status, 1, HAL_MAX_DELAY);
	if((status & STATUS_GOOD) != STATUS_GOOD){
		return HAL_ERROR;
	}
	return ret;
}


void ath2x_read(ath2x_t *sensor){
	uint8_t data[7];
	data[0] = TRIGGER_MEASUREMENT;
	data[1] = MEASUREMENT_F_BYTE;
	data[2] = MEASUREMENT_S_BYTE;
	HAL_I2C_Master_Transmit(sensor->hi2c, sensor->adress, data, 3, HAL_MAX_DELAY);
	HAL_Delay(80);

	HAL_I2C_Master_Receive(sensor->hi2c, sensor->adress, status, 7, HAL_MAX_DELAY);

	uint32_t humidity_raw = (data[1] << 12) | (data[2] << 4) | (data[3] & 0xF0);
	sensor->humidity = (float)humidity_raw * 100.0f / 1048576.0f;

	uint32_t temperature_raw = ((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5];
	sensor->temperature = (float)temperature_raw * 200.0f / 1048576.0f - 50.0f;
}

