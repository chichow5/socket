/*
 * transferstuff.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _TRANSFER_STUFF_H
#define _TRANSFER_STUFF_H

#include "basic.h"
#include "networkpacket.h"
#include "debug.h"

void RecvByLength(int connfd, int len, void *des);

void SendByLength(int connfd, int len, void *sou);

void RecvHeader(int sockfd, Header *header);
void SendHeader(int sockfd, Header *header);
void SendText(int sockfd, int len, char *sou);
void RecvText(int sockfd, int len, char *des);
void SendFile(int sockfd, char *path);
void RecvFile(int sockfd, int len, char *path);

#endif //_TRANSFER_STUFF_H