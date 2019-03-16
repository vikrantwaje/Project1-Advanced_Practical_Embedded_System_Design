#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

/*Thread function prototypes*/
void *socket_thread( void*);
void *temperature_thread( void*);
void *light_sensor_thread( void*);
void *logger_thread( void*);
void set_sig_handler(void);
long getMicrotime();

/*GLOBAL VARIABLES*/
/*For socket_thread*/
char *RxBuf[10] = {0};
int socket_fd;
int check_stat;
int sig_flag = 0;
int sock_stat;

/*For temperature_thread*/


/*MACROS*/
/*For socket_thread*/
#define	PORT_NUM	(7000)


#endif /* SRC_MAIN_H_ */