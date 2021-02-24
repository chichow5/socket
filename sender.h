/*
 * sender.h
 * socket
 *
 * Created by Chi Chow on 2021-2-24
 *
*/

#ifndef SENDER_H
#define SENDER_H

#ifdef _WIN32
#include "core/winbasic.h"
#else
#include "core/basic.h"
#endif

#include "core/bridge.h"
#include "core/networkpacket.h"
#include "core/transferstuff.h"

void SendFile(char *ip, int port, char *path);

void SendText(char *ip, int port, char *path);

#endif // SENDER_H
