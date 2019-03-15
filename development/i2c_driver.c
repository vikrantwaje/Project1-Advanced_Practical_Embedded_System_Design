
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>
#include<stdint.h>
#include<stdlib.h>

typedef enum{
	WRITE_REG_SUCCESS, READ_REG_SUCCESS, WRITE_REG_FAIL, READ_REG_FAIL

}temp_sensor_status_t;

typedef enum{
	REQUEST_CELSIUS, REQUEST_KELVIN, REQUEST_FARHENHEIT
}request_cmd_t;


typedef enum{
	FAULT,EM,CONVERSION_RATE,SD_MODE,RESOLUTION,ALL
}reg_read_cmd_t;

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

const char *path_name = "/dev/i2c-2";


temp_sensor_status_t write_ptr_reg(uint8_t address){
	int status = 0;
	int n =0;
	int fptr = open(path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,TEMP_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;
	}
	n= write(fptr,&address,1);
	if(n == -1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;
	}
	close(fptr);
	return WRITE_REG_SUCCESS;
}


temp_sensor_status_t write_reg(uint8_t address, uint16_t data){
	int status =0;
	int fptr = 0;
	int n = 0;
	uint8_t *buffer = malloc(sizeof(uint8_t) *5);
	*(buffer + 0) = (address);
	*(buffer + 1) = ((data & 0xFF00)>>8);
	*(buffer + 2) = ((data) & 0x00FF);

	fptr = open(path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,TEMP_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;
	}
	n = write(fptr,buffer,3);
	if(n ==-1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;
	}
	close(fptr);
	free(buffer);
	return WRITE_REG_SUCCESS;
}


temp_sensor_status_t read_reg(uint8_t address, uint8_t *data,reg_read_cmd_t command){
	int status =0;
	int fptr = 0;
	int n = 0;
	fptr = open(path_name,O_RDWR);	
	if(fptr == -1){
		perror("Error in opening the file");
		return WRITE_REG_FAIL;
	}
	status = ioctl(fptr,I2C_SLAVE,TEMP_SENSOR_I2C_ADDRESS);
	if(status !=0){
		perror("IOCTL function failed");
		return WRITE_REG_FAIL;
	}
	n =write(fptr,&address,1);
	if(n==-1){
		perror("Write not successfull");
		return WRITE_REG_FAIL;
	}

	n = read(fptr,(data ),2);
	if(n ==-1){
		perror("Read not successfull");
		return READ_REG_FAIL;
	}

	//swap the values: Using XOR swap
	*(data + 0) = *(data +0) ^ *(data +1);
	*(data +1) = *(data +0) ^ *(data +1);
	*(data +0) = *(data +0) ^ *(data +1);
	if(command == SD_MODE){
	*(data + 0) =*(data + 1);
	*(data + 1) =0;
}	
else if(command == FAULT){
	*(data + 0) = *(data + 1)>>3;
	*(data + 1) = 0;
}

else if(command == EM){
	*(data + 0) = *(data +0)>>4;
	*(data + 1) = 0;
}

else if(command == CONVERSION_RATE){

	*(data +0) = *(data + 0)>>6;
	*(data +1) =0;
}
else if(command == RESOLUTION){
	*(data + 0) = *(data + 1)>>5;
	*(data + 1) =0;

}
else{
	*(data +0 )= *(data +0);
	*(data + 1) = *(data +1);
}
	close(fptr);
	return READ_REG_SUCCESS;
}


double get_temperature(request_cmd_t request){


	double result = 0;
	double multiplier =0;
	uint8_t *data = malloc(sizeof(uint8_t) * 2);
	if(request == REQUEST_CELSIUS){
		multiplier =0.0625;
	}
	else if(request == REQUEST_CELSIUS){
		multiplier =0.0625;
	}	
	else{
		multiplier = 0.0625;
	}	int status = read_reg(TEMPERATURE_REG,data,ALL);
	if(status !=READ_REG_SUCCESS){

		perror("Reading configuration register failed");


	}
	printf("%x %x",*(data + 0),*(data +1));

	int32_t temp = (((*(data + 1)<<8) |*(data +0))>>4);
	if(temp & 0x800 !=0x800)
		result = temp * multiplier;
	else
		result = -1*((~(temp) +1) * multiplier);

	return result;


	free(data);
}

void main(){

	int status = 0;
//	uint8_t *send_data = malloc(sizeof(uint8_t)*10);
	uint8_t *receive_data = malloc(sizeof(uint8_t) *10);

	/*	*(send_data + 0) =0x10;
	 *(send_data +1) =0x20;
	 status =write_reg(TLOW_REG,send_data);
	 if(status !=WRITE_REG_SUCCESS){

	 perror("writing configuration register failed");
	 }*/

	/*status = read_reg(TEMPERATURE_REG,receive_data);
	  if(status !=READ_REG_SUCCESS){

	  perror("Reading configuration register failed");


	  }*/
	printf("\n\r%lf",get_temperature(REQUEST_CELSIUS));
	//printf("%x %x",*(receive_data + 0),*(receive_data +1));
	free(receive_data);
}