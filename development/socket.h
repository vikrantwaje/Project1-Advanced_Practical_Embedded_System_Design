#ifndef SRC_SOCKET_H_
#define	SRC_SOCKET_H_

/*GLOBAL VARIABLES*/
/*For socket_thread*/
char *RxBuf[10] = {0};
int socket_fd;
int check_stat;
int sig_flag = 0;
int sock_stat;


/*MACROS*/
/*For socket_thread*/
#define	PORT_NUM	(7000)


#endif	SRC_SOCKET_H_
