/*
 * fakedaemon.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "fakedaemon.h"

void daemon(int port){
    int     listenfd, connfd;
    int     childpid;
    ssize_t n;

    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    listen(listenfd, 20);

    for( ; ; ){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *)&cliaddr, &clilen);
        if ((childpid = fork()) == 0){
            close(listenfd);

            Header header(0);
            ReadByLength(connfd, H_LEN, &header);
            if (header.length > H_LEN){
                ReadByLength(connfd, header.length-H_LEN, header.payloadInfo);
            }
            printf("%s\n",header.payloadInfo);
            exit(0);
        }
        close(connfd);
    }
}