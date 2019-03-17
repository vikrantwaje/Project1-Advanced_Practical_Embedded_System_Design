#ifndef SRC_TEMP_H_
#define SRC_TEMP_H_

typedef enum{
	WRITE_REG_SUCCESS, READ_REG_SUCCESS, WRITE_REG_FAIL, READ_REG_FAIL

}temp_sensor_status_t;

typedef enum{
	REQUEST_CELSIUS, REQUEST_KELVIN, REQUEST_FARHENHEIT
}request_cmd_t;


typedef enum{
	FAULT,EM,CONVERSION_RATE,SD_MODE,RESOLUTION,ALL
}reg_read_cmd_t;

/*MACROS*/
/*For temperature_thread*/
#define TEMP_SENSOR_I2C_ADDRESS (0x48)
#define TEMPERATURE_REG		(0x00)
#define CONFIGURATION_REG	 (0x01)
#define TLOW_REG		(0x02)
#define THIGH_REG		(0x03)

#define CONVERSION_RATE_0_25	((0x00)<<6U)
#define CONVERSION_RATE_1	((0x01)<<6U)
#define CONVERSION_RATE_4	((0x02)<<6U)
#define CONVERSION_RATE_8	((0x03)<<6U)

#define SHUTDOWN_ON		((0x01)<<8U)
#define SHUTDOWN_OFF		((0x00)<<8U)

#define EM_ON			((0x01)<<4U)
#define EM_OFF			((0x00)<<4U)

#define FAULT_1			((0x00)<<11U) 
#define FAULT_2			((0x01)<<11U)
#define FAULT_3			((0x02)<<11U)
#define FAULT_4			((0x03)<<11U)


/*function prototypes with return types*/
temp_sensor_status_t write_ptr_reg(uint8_t address);
temp_sensor_status_t write_reg(uint8_t address, uint16_t data);
temp_sensor_status_t read_reg(uint8_t address, uint8_t *data,reg_read_cmd_t command);
double get_temperature(request_cmd_t request);


#endif	SRC_TEMP_H_
