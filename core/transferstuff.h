/*
 * transferstuff.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _TRANSFER_STUFF_H
#define _TRANSFER_STUFF_H

#include <cstdio>
#include <cstring>
#include "basic.h"
#include "networkpacket.h"
#include "debug.h"

int RecvHeader(int sockfd, Header *header);

int SendHeader(int sockfd, Header *header);

int SendText(int sockfd, int len, char *sou);

int RecvText(int sockfd, int len, char *des);

int SendFile(int sockfd, char *path);

int RecvFile(int sockfd, int len, char *path);

#endif //_TRANSFER_STUFF_H