# Project 1:  BeagleBone Linux System Design

An I2C-based multithreaded application that runs on BeagleBone and acquires temperature and light intensity data from sensors and responds to commands and communications from an external client.

## Authors: Vikrant Waje, Tanmay Chaturvedi

## FILENAME: temp_sensor.c

### Supported Functions:

```C
#include <temp_sensor.h>
sensor_status_t write_ptr_reg(uint8_t address);
```
- Responsible for writing into pointer register of temperature sensor TMP102


```C
#include <temp_sensor.h>
sensor_status_t temperature_write_reg(uint8_t address, uint16_t data);
```
- Responsible for writing into  register of temperature sensor TMP102

```C
#include <temp_sensor.h>
sensor_status_t temperature_read_reg(uint8_t address, uint8_t *data,reg_read_cmd_t command);
```

 - Responsible for reading from  register of temperature sensor TMP102
```C
#include <temp_sensor.h>
double get_temperature(request_cmd_t request);
```
- Read the value from temperature register

## FILENAME: light_sensor.c

### Supported Functions:

```C
#include <light_sensor.h>
sensor_status_t light_write_reg(uint8_t address, uint8_t data);
```
- Responsible for writing into  register of light sensor
```C
#include <light_sensor.h>
sensor_status_t light_read_reg(uint8_t address, uint8_t *data,read_cmd_t command);
```
- Responsible for reading from register of light sensor

```C
#include <light_sensor.h>
sensor_status_t read_two_reg(uint8_t address, uint8_t *data);
```
- Responsible for reading from two  register of light sensor
```C
#include <light_sensor.h>
double read_lux();
```
- Responsible for reading lux value from light sensor

```C
#include <light_sensor.h>
sensor_status_t light_sensor_power_on();
```
- Responsible for turning On light sensor before reading any data


## FILENAME: server.c

### Supported Functions:

```C
#include <server.h>
int server_establish(void);
```
- After connecting with external client, receives command from client and call respective function


## FILENAME: thread.c

### Supported Functions:

```C
#include <thread.h>
void *socket_thread( void*);
```
- Waits for a connection initiated by an external client. Once connected, accepts commands from client and acts accordingly. If clients commands the connection to "close", server thread disconnects, closes the socket connection and waits for a new connection

```C
#include <thread.h>
void *temperature_thread( void*);
```
- Get the temperature value periodically from temperature sensor and logs into file opened by logger thread

```C
#include <thread.h>
void *light_sensor_thread( void*);
```
- Get the LUX values from light sensor attached using I2C interface and report it periodically to logger thread

```C
#include <thread.h>
 void *logger_thread( void*);
```
- Log the values of temperature, light sensor and socket status in log file created by logger task into file opened by logger thread

