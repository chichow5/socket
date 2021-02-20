/*
 * basic.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "basic.h"

int setupClient(struct sockaddr_in *servaddr, char *ip, int port, int *sockfd){
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(servaddr, 0, sizeof(servaddr));
    servaddr->sin_family = AF_INET;
    servaddr->sin_port = htons(port);
    servaddr->sin_addr.s_addr = inet_addr(ip);
}

int Socket(int __domain, int __type, int __protocol)
{
	int re;
	if ((re = socket(__domain, __type, __protocol)) < 0){
		//error code here
	}
	return re;
}

int Bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
{
	int re;
	if((re = bind(__fd, __addr, __len)) < 0){
		//error code here
	}
	return re;
}

int Connect(int __fd, __SOCKADDR_ARG __addr, socklen_t __len)
{
	int re;
	if ((re = connect(__fd, __addr, __len)) < 0){
		//error code here
	}
	return re;
}

int Accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len)
{
	int re;
	if ((re = accept(__fd, __addr, __addr_len)) < 0){
		//error code here
	}
	return re;
}
