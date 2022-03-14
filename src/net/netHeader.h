#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/epoll.h>

#define SIN_ADDR1 "175.178.123.237" 
#define SIN_ADDR2 "47.106.133.127" 

#define SIN_PORT1 6666
#define SIN_PORT2 8888