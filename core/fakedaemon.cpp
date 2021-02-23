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
//    ssize_t n;

    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    listen(listenfd, 20);

/*
    for( ; ; ){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *)&cliaddr, &clilen);
        if ((childpid = fork()) == 0){
            printf("connection from client...\n");
            close(listenfd);

            Header header;//(0);
            RecvHeader(connfd, &header);

            header.payloadInfo[header.length-H_LEN] = 0;
            header.show();
            close(connfd);
            exit(0);
        }
        close(connfd);
    }
    */
}