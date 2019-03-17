
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>
#include<stdint.h>
#include<stdlib.h>
#include "temp_sensor.h"


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


	//double result = 0;
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
	//printf("%x %x",*(data + 0),*(data +1));

	int32_t digitalTemp =0;

	// Bit 0 of second byte will always be 0 in 12-bit readings and 1 in 13-bit
	if(*(data + 0)&0x01)	// 13 bit mode
	{
		// Combine bytes to create a signed int
		digitalTemp = (*(data + 1) << 5) | (*(data + 0) >> 3);
		// Temperature data can be + or -, if it should be negative,
		// convert 13 bit to 16 bit and use the 2s compliment.
		if(digitalTemp > 0xFFF)
		{
			digitalTemp |= 0xE000;
		}
	}
	else	// 12 bit mode
	{
		// Combine bytes to create a signed int 
		digitalTemp = (*(data + 1) << 4) | (*(data + 0) >> 4);
		// Temperature data can be + or -, if it should be negative,
		// convert 12 bit to 16 bit and use the 2s compliment.
		if(digitalTemp > 0x7FF)
		{
			digitalTemp |= 0xF000;
		}
	}
	// Convert digital reading to analog temperature (1-bit is equal to 0.0625 C)

	free(data);
	return (digitalTemp*multiplier);


	//	free(data);
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
	while(1)
	printf("\n\r%lf",get_temperature(REQUEST_CELSIUS));
	//printf("%x %x",*(receive_data + 0),*(receive_data +1));
	free(receive_data);
}
