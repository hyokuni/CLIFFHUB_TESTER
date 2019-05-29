
#ifndef INA226_H
#define INA226_H

#define SLAVE_BUFFER_SIZE				(0x100)
#define SLAVE_BUFFER_MASK(value)		((SLAVE_BUFFER_SIZE - 1) & (value))

#define BATTERY_I2C_CONTROL				(0x10)
#define BATTERY_I2C_REMAINING_CAPACITY	(0x12)
#define BATTERY_I2C_VOLTAGE				(0x14)
#define BATTERY_I2C_CURRENT				(0x16)
#define BATTERY_I2C_TEMPERATURE			(0x18)
#define BATTERY_I2C_CYCLE_COUNT			(0x1a)
#define BATTERY_I2C_CELL_A				(0x1c)
#define BATTERY_I2C_CELL_B				(0x1e)

#define CLIFF_I2C_REG_CH0				(0x20)
#define CLIFF_I2C_REG_CH1				(0x22)
#define CLIFF_I2C_REG_CH2				(0x24)
#define CLIFF_I2C_REG_CH3				(0x26)
#define CLIFF_I2C_REG_CH4				(0x28)
#define CLIFF_I2C_REG_CH5				(0x2a)
#define CLIFF_I2C_REG_CH6				(0x2c)
#define CLIFF_I2C_REG_CH7				(0x2e)
#define CLIFF_I2C_REG_CHD				(0x36)

#define CLIFF_I2C_REG_STATUS			(0x30)
#define CLIFF_I2C_REG_PRESENT			(0x31)
#define CLIFF_I2C_REG_ENABLED			(0x32)
#define CLIFF_I2C_REG_ERROR				(0x33)
#define CLIFF_I2C_REG_RANGE				(0x34)

#define CLIFF_I2C_MASK_CH0				(0x01)
#define CLIFF_I2C_MASK_CH1				(0x02)
#define CLIFF_I2C_MASK_CH2				(0x04)
#define CLIFF_I2C_MASK_CH3				(0x08)
#define CLIFF_I2C_MASK_CH4				(0x10)
#define CLIFF_I2C_MASK_CH5				(0x20)
#define CLIFF_I2C_MASK_CH6				(0x40)
#define CLIFF_I2C_MASK_CH7				(0x80)
#define CLIFF_I2C_MASK_CHD				(0x00)


#define BATTERY_I2C_CONTROL_RESET		(0x01)

#define CLIFF_I2C_RANGE_HIGH_ACCURACY	(0)		/*!< High accuracy mode */
#define CLIFF_I2C_RANGE_HIGH_SPEED		(1)		/*!< High speed mode */
#define CLIFF_I2C_RANGE_LONG_RANGE		(2)		/*!< Long range mode */

#define MAX_CURRENT						80000

HAL_StatusTypeDef INA226_Loop(void);
//extern uint8_t aSlaveBuffer[SLAVE_BUFFER_SIZE];

#endif // INA226_H_H

