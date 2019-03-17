#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

typedef enum{
	WRITE_REG_SUCCESS = 1, READ_REG_SUCCESS =2, WRITE_REG_FAIL=-1, READ_REG_FAIL=-2

}light_sensor_status_t;

typedef enum{
	REQUEST_CELSIUS, REQUEST_KELVIN, REQUEST_FARHENHEIT
}request_cmd_t;

typedef enum{
	INTEGRATION_TIME, GAIN
}read_cmd_t;

/*MACROS*/
/*For light_sensor_thread*/
#define LIGHT_SENSOR_I2C_ADDRESS (0x39)
#define CONTROL_REG	 	(0x00)
#define TIMING_REG		(0x01)
#define THRESHLOWLOW_REG	(0x02)
#define THRESHLOWHIGH_REG	(0x03)
#define THRESHHIGHLOW_REG	(0x04)
#define THRESHHIGHHIGH_REG	(0x05)
#define INTERRUPT_REG		(0x06)
#define CRC			(0x08)
#define ID_REG			(0x0A)
#define DATA0LOW_REG		(0x0C)
#define DATA0HIGH_REG		(0x0D)
#define DATA1LOW_REG		(0x0E)
#define DATA1HIGH_REG		(0x0F)

#define	INTEGRATION_13_7	((0x00))
#define INTEGRATION_101		((0x01))
#define INTEGRATION_402		((0x02))

#define LOW_GAIN		((0x00)<<4U)
#define HIGH_GAIN		((0x01)<<4U)


#define COMMAND_BIT		(0x80)
#define WORD_OPERATION_BIT	(0x20)

/*Function Prototypes*/
light_sensor_status_t write_reg(uint8_t address, uint8_t data);
light_sensor_status_t read_reg(uint8_t address, uint8_t *data,read_cmd_t command);
light_sensor_status_t read_two_reg(uint8_t address, uint8_t *data);
double read_lux();

#endif	SRC_LIGHT_H_
