/*
 * bridge.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _BRIDGE_H
#define _BRIDGE_H 1

#ifndef _WIN32
#include "basic.h"
#else
#include "winbasic.h"
#endif

int GetFileLength(const char *path);

#endif //_BRIDGE_H 1