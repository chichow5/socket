/*
 * winbasic.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-22
 *
*/

#ifndef _WINBASIC_H
#define _WINBASIC_H 1

#define socklen_t int
#define close closesocket

#define BUFFSIZE 4096
#define PORT 54123
#define SA struct sockaddr
#define MAXLINE 4096

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdarg>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

void err_msg(const char* fmt, ...);

void err_exit(const char* fmt, ...);

void SetupClient(struct sockaddr_in* servaddr, char* ip, int port, SOCKET* sockfd);

SOCKET Socket(int af, int type, int protocol);

int Bind(SOCKET s, const struct sockaddr* name, int namelen);

int Connect(SOCKET s, const struct sockaddr* name, int namelen);

SOCKET Accept(SOCKET s, struct sockaddr* addr, int* addrlen);

#endif //_WINBASIC_H