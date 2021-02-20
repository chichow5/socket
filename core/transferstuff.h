/*
 * transferstuff.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _FILETRANSFER_H
#define _FILETRANSFER_H

#include <cstdio>
#include <cstring>
#include "basic.h"

int ReadByLength(int sockfd, int len, void *item);

int ReadToFile(int sockfd, int len, FILE *fp);


#endif //_FILETRANSFER_H