#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>


#define I2C_ADDRESS (0x48)

int main(){
	int f;
	int n;
	char buf[10],read_buf[10];
	char write_buf[10];
	buf[0]=0x02;
	buf[1]=0x8e;
	buf[2] =0x70;
	

	f = open("/dev/i2c-2",O_RDWR);	
	ioctl(f,I2C_SLAVE,I2C_ADDRESS);
	//n= write(f,2,1);
	n= write(f,buf,3);
	
	
	n= write(f,2,1);
	n =read(f,read_buf,2);
	printf("%x %x",read_buf[0],read_buf[1]);
	close(f);
//	n = read(f,buf,2);	


}
