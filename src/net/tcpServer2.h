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

int init()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        printf("socket error\n");
        return -1;
    }

    // listen()
    struct sockaddr_in ser_addr;
    struct sockaddr_in cli_addr;
    socklen_t clienLen;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(socket_fd, (sockaddr*)&ser_addr, sizeof(ser_addr));
    if (ret == -1)
    {
        printf("bind error errno=%d", errno);
        return -2;
    }
    listen(socket_fd, 128);

    int epoll_fd = epoll_create(5);

    if (epoll_fd == -1)
    {
        printf("epoll_create error");
        return -3;
    }

    

    
    
}