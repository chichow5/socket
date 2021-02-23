/*
 * transferstuff.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _TRANSFER_STUFF_H
#define _TRANSFER_STUFF_H

#ifndef _WIN32
#include "basic.h"
#else
#include "winbasic.h"
#endif
#include "networkpacket.h"
#include "debug.h"

void RecvByLength(SOCKET connfd, int len, void *des);

void SendByLength(SOCKET connfd, int len, void *sou);

void RecvHeader(SOCKET sockfd, Header *header);

void SendHeader(SOCKET sockfd, Header *header);

void SendText(SOCKET sockfd, int len, char *sou);

void RecvText(SOCKET sockfd, int len, char *des);

void SendFile(SOCKET sockfd, char *path);

void RecvFile(SOCKET sockfd, int len, char *path);

#endif //_TRANSFER_STUFF_H