/*
 * sender.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-24
 *
*/
#include "sender.h"

void SendFile(char *ip, int port, char *path)
{
    fprintf(stderr, "Send %s to %s:%d\n", path, ip, port);
    struct sockaddr_in servaddr;
    SOCKET sockfd;
    Header header;
    header.setPayloadInfo(ResolveFileName(path)+path);
    header.attachFile(path);

    SetupClient(&servaddr, ip, port, &sockfd);
    Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    SendHeader(sockfd, &header);
    SendFile(sockfd, path);

    closesocket(sockfd);
}

void SendText(char *ip, int port, char *text)
{
    struct sockaddr_in servaddr;
    SOCKET sockfd;
    Header header;
    header.attachText(text, FLAG_TEXT);
    SetupClient(&servaddr, ip, port, &sockfd);
    Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    SendHeader(sockfd, &header);
    SendText(sockfd, strlen(text), text);

    closesocket(sockfd);
}
