/*
 * receiver.h
 * socket
 *
 * Created by Chi Chow on 2021-2-24
 *
*/

#ifndef REVEIVER_H
#define REVEIVER_H

#ifdef _WIN32
#include "core/winbasic.h"
#else
#include "core/basic.h"
#endif

#include "core/bridge.h"
#include "core/networkpacket.h"
#include "core/transferstuff.h"

#include <signal.h>

#ifdef _WIN32
struct Param{
    SOCKET connfd;
    char *folder;
};

void subserver(Param *param); //for windows NT Thread
#endif

void Daemon(int port, char* folder);

void HeaderHandler(SOCKET connfd, Header& header);

#endif // REVEIVER_H
