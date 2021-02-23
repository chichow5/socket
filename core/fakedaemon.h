/*
 * fakedaemon.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _FAKEDAEMON_H
#define _FAKEDAEMON_H 1

#include <cstdio>
#ifndef _WIN32
#include <bits/types.h>
#include "basic.h"
#else
#include "winbasic.h"
#endif
#include "networkpacket.h"
#include "transferstuff.h"

void daemon(int port);

#endif //_FAKEDAEMON_H