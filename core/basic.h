/*
 * basic.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _BASIC_H
#define _BASIC_H 1

#define BUFFSIZE 4096
#define PORT 54123
#define SA struct sockaddr
#define MAXLINE 4096

#include <cstdio>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdarg>

void err_msg(const char *fmt, ...);

void err_exit(const char *fmt, ...);

void setupClient(struct sockaddr_in *servaddr, char *ip, int port, int *sockfd);

int Socket(int __domain, int __type, int __protocol);

int Bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t len);

int Connect(int __fd, __SOCKADDR_ARG __addr, socklen_t __len);

int Accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len);


#endif //_BASIC_H