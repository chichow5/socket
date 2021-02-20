#ifndef _BASIC_H
#define _BASIC_H 1

#define BUFFSIZE 4096
#define PORT 54123
#define SA struct sockaddr

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int Socket(int __domain, int __type, int __protocol);

int Bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t len);

int Connect(int __fd, __SOCKADDR_ARG __addr, socklen_t __len);

int Accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len);

#endif //_BASIC_H