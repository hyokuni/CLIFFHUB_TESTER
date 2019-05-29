///* Includes */
///* ================================================================================ */
//#include "main.h"
//#include "stm32f4xx_hal.h"
//
////#include "cliff.h"
//
//
///* defines & macros */
///* ================================================================================ */
//
//#define I2C_I2C_ADDRESS_READ					0xA6
//#define I2C_I2C_ADDRESS_WRITE					0xA4
//
//#define INA226_I2C_ADDR_CONFIG					(0x00)
//#define INA226_I2C_ADDR_SHUNT					(0x01)
//#define INA226_I2C_ADDR_BUS_VOLTAGE				(0x02)
//#define INA226_I2C_ADDR_POWER					(0x03)
//#define INA226_I2C_ADDR_CURRENT					(0x04)
//#define INA226_I2C_ADDR_CALIBRATION				(0x05)
//#define INA226_I2C_ADDR_MASK_ENABLE				(0x06)
//#define INA226_I2C_ADDR_ALERT_LIMIT				(0x07)
//#define INA226_I2C_ADDR_MANUFACTURER_ID			(0xFE)
//#define INA226_I2C_ADDR_DIE_ID					(0xFF)
//
//
////#define debug_printf				uart_printf
//#define debug_printf				printf
//#define collect_uart				// for ΌφΑύ
//
//
///* externs */
///* ================================================================================ */
//
//extern I2C_HandleTypeDef hi2c1;
//
//static HAL_StatusTypeDef I2C_ReadWord(uint8_t address, uint16_t * pvalue)
//{
//	HAL_StatusTypeDef result;
//
//	uint8_t data[2];
//
//	if((result = HAL_I2C_Master_Transmit(&hi2c1, I2C_I2C_ADDRESS_READ, &address, 1, 1000)) != HAL_OK)
//	{
//		*pvalue = 0xffff;
//		return result;
//	}
//
//	if((result = HAL_I2C_Master_Receive(&hi2c1, I2C_I2C_ADDRESS_READ, data, 2, 1000)) != HAL_OK)
//	{
//		*pvalue = 0xffff;
//		return result;
//	}
//
//	*pvalue = (uint16_t) ((data[0] << 8) | data[1]);
//	return HAL_OK;
//}
//
///* ================================================================================ */
//
//static HAL_StatusTypeDef I2C_WriteWord(uint8_t address, uint16_t pvalue)
//{
//	HAL_StatusTypeDef result;
//
//	uint8_t data[3];
//
//	data[0] = address;
//	data[1] = (pvalue >> 8) & 0xFF;
//	data[2] =  pvalue & 0xFF;
//
//
//	if((result = HAL_I2C_Master_Transmit(&hi2c1, I2C_I2C_ADDRESS_WRITE, data, 3, 1000)) != HAL_OK)
//	{
//		pvalue = 0xffff;
//		return result;
//	}
//
//
//	return HAL_OK;
//}
//
//HAL_StatusTypeDef INA226_Init(void)
//{
//	//if(maxCurrent == 0 | maxCurrent > 10000)
//	//	return HAL_ERROR;
//
//	//I2C_WriteWord(INA226_I2C_ADDR_CONFIG,0x412F);
//
//
//	I2C_WriteWord(INA226_I2C_ADDR_CALIBRATION,0x7FFF);
//
//	return HAL_OK;
//}
//
//
//static HAL_StatusTypeDef I2C_ReadCells(uint16_t * cellA, uint16_t * cellB)
//{
//	HAL_StatusTypeDef result;
//
//	uint8_t buffer[36];
//	uint8_t sum;
//	int index;
//
//	buffer[0] = 0x3e;
//	buffer[1] = 0x71;
//	buffer[2] = 0x00;
//
//	sum = 0x71;
//
//	if((result = HAL_I2C_Master_Transmit(&hi2c1, INA226_I2C_ADDRESS, buffer, 3,  1000)) != HAL_OK)
//	{
//		*cellA = 0xffff;
//		*cellB = 0xffff;
//		return result;
//	}
//
//	if((result = HAL_I2C_Master_Receive(&hi2c1, INA226_I2C_ADDRESS, buffer, 34, 1000)) != HAL_OK)
//	{
//		*cellA = 0xffff;
//		*cellB = 0xffff;
//		return result;
//	}
//
//	for(index = 0; index < 32; index++)
//		sum += buffer[index];
//
//	sum = ~sum;
//
//	if(sum == buffer[32])
//	{
//		*cellA = (uint16_t) ((buffer[1] << 8) | buffer[0]);
//		*cellB = (uint16_t) ((buffer[3] << 8) | buffer[2]);
//		return HAL_OK;
//	}
//
//	*cellA = 0xffff;
//	*cellB = 0xffff;
//	return HAL_ERROR;
//}
//
///* ================================================================================ */
//
//HAL_StatusTypeDef Cliff_Loop(void)
//{
//	HAL_StatusTypeDef result;
//
//	//uint16_t * pBuffer;
//
//	static uint16_t shunt;
//
//
//	static int res_bus_voltage;
//	static int res_shunt;
//	static int res_current;
//
//
//	result = HAL_OK;
//
//	do
//	{
//
//		/* read parameters from the battery */
//		if(I2C_ReadWord(INA226_I2C_ADDR_SHUNT, &shunt) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_BUS_VOLTAGE, &bus_voltage) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_POWER, &power) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_CURRENT, &current) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_CALIBRATION, &calibration) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_MASK_ENABLE, &mask) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_ALERT_LIMIT, &alert_limit) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_MANUFACTURER_ID, &manufacturer_id) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_DIE_ID, &die_id) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		if(I2C_ReadWord(INA226_I2C_ADDR_CONFIG, &config) != HAL_OK)
//		{
//			result = HAL_ERROR;
//			break;
//		}
//
//		//if(I2C_ReadCells(&cellA, &cellB) != HAL_OK)
//		//{
//		//	result = HAL_ERROR;
//		//	break;
//		//}
//	}
//	while(0);
//
//	if(result != HAL_OK)
//	{
//
//	}
//
//	/* store parameters to I2C slave buffer */
//	__disable_irq();
//
//	__enable_irq();
//
//	/* print */
//
//
//
//	if(result == HAL_OK)
//	{
//		res_bus_voltage = (float)bus_voltage * 1.25;
//		res_shunt = (float)shunt * 2.5;
//		res_current = ((res_shunt * 0.000001) / 0.002) * 1000;
//
//		if(res_current == 0 || res_current > MAX_CURRENT){
//
//		}
//		else{
//		#ifdef reserveddd
//		debug_printf("shunt V: %d \n", shunt);
//		debug_printf("bus_voltage : %d \n", bus_voltage);
//		debug_printf("Power W: %d \n", power);
//		debug_printf("Current C: %d \n",current);
//		debug_printf("Calibration %d \n", calibration);
//		debug_printf("mask %d\n", mask);
//		debug_printf("alert_limit %d\n", alert_limit);
//		debug_printf("manufacturer_id %d\n", manufacturer_id);
//		debug_printf("die_id %d\n",die_id);
//		debug_printf("config %d\n", config);
//		debug_printf("")
//
//		debug_printf("\n");
//		#endif
//
//		#ifndef collect_uart
//		//debug_printf("shunt V: %d \n", (~shunt)+1);
//		debug_printf("shunt V: %d \n", shunt);
//		debug_printf("shunt(conv) V: %d \n", res_shunt);
//		//debug_printf("bus_voltage : %d \n", bus_voltage);
//		debug_printf("bus_voltage(conv) : %d \n", res_bus_voltage);
//		debug_printf("config 0x%x\n", config);
//		//debug_printf("Calibraiton data W: %d \n", calibration);
//		//debug_printf("Power W: %d \n", power);
//		//debug_printf("Current C: %d \n",current);
//
//		debug_printf("res_current : %d \n", res_current);
//		debug_printf("\n");
//		#endif
//
//
//		#ifdef	collect_uart
//		debug_printf("%4dmV,%4dmA\n",res_bus_voltage,res_current);
//		//debug_printf("\n");
//		#endif
//		}
//	}
//	else
//	{
//		debug_printf("ERROR Interface with INA226.\n\n");
//	}
//
//	return result;
//}
//
///* ================================================================================ */
//
//#ifdef __cplusplus
//}
//#endif
//
