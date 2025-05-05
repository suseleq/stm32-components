/*
 * ATH2X.h
 *
 *  Created on: May 5, 2025
 *      Author: Kuba
 */

#ifndef INC_ATH2X_H_
#define INC_ATH2X_H_

#define AHT2x_ADRESS		0x38

#define	GET_STATUS			0x71

#define	STATUS_GOOD			0x18

#define INIT_REGISTER_1		0x1B
#define INIT_REGISTER_2		0x1C
#define INIT_REGISTER_3		0x1E

#define TRIGGER_MEASUREMENT	0xAC
#define MEASUREMENT_F_BYTE	0x33
#define MEASUREMENT_S_BYTE	0x00


typedef struct{
	I2C_HandleTypeDef *hi2c;
	uint8_t adress;
	float temperature;
	float humidity;
} ath2x_t;

HAL_StatusTypeDef  ath2x_init(ath2x_t *sensor, I2C_HandleTypeDef *hi2c);
void ath2x_read(ath2x_t *sensor);

#endif /* INC_ATH2X_H_ */
