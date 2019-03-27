# Project 1:  BeagleBone Linux System Design

An I2C-based multithreaded application that runs on BeagleBone and acquires temperature and light intensity data from sensors and responds to commands and communications from an external client.

## Authors: Vikrant Waje, Tanmay Chaturvedi

## FILENAME: temp_sensor.c

### Supported Functions:

```
#include <temp_sensor.h>
sensor_status_t write_ptr_reg(uint8_t address);
```
- Responsible for writing into pointer register of temperature sensor TMP102


```
#include <temp_sensor.h>
sensor_status_t temperature_write_reg(uint8_t address, uint16_t data);
```
- Responsible for writing into  register of temperature sensor TMP102

```
#include <temp_sensor.h>
sensor_status_t temperature_read_reg(uint8_t address, uint8_t *data,reg_read_cmd_t command);
```

 - Responsible for reading from  register of temperature sensor TMP102
```
#include <temp_sensor.h>
double get_temperature(request_cmd_t request);
```
- Read the value from temperature register

## FILENAME: light_sensor.c

### Supported Functions:

```
#include <temp_sensor.h>
double get_temperature(request_cmd_t request);
```
- Read the value from temperature register
```
#include <temp_sensor.h>
double get_temperature(request_cmd_t request);
```
- Read the value from temperature register

```
#include <temp_sensor.h>
double get_temperature(request_cmd_t request);
```
- Read the value from temperature register
```
#include <temp_sensor.h>
double get_temperature(request_cmd_t request);
```
- Read the value from temperature register