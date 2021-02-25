/*
 * receiver.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-24
 *
*/

#include "receiver.h"

void Daemon(int port, char* folder){
#ifndef _WIN32
    signal(SIGCLD,SIG_IGN);
#endif

    SOCKET  listenfd,connfd;
#ifndef _WIN32
    int     childpid;
#endif

    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    listen(listenfd, 20);

    fprintf(stderr, "start listening on port %d\n",port);

    for( ; ; ){
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
#ifndef _WIN32
        if ((childpid = fork()) == 0){
            close(listenfd);

            Header header(MAXLINE);
            RecvHeader(connfd, &header);
            std::string path(folder);
            if (path[path.length()-1]!=92 && path[path.length()-1]!=47){
#ifdef _WIN32
                path.append("\\");
#else
                path.append("/");
#endif
            }
            path.append(header.payloadInfo);
            header.setPayloadInfo(path);
            HeaderHandler(connfd, header);
            close(connfd);
            exit(EXIT_SUCCESS);
        }
#else
        Param param;
        param.connfd = connfd;
        param.folder = folder;
        HANDLE hThread;
        if ((hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&subserver, &param, 0, NULL)) == NULL) {
            err_msg("failed to create sub thread");
        }
        if (hThread != 0) {
            WaitForSingleObject(hThread, INFINITE);
            CloseHandle(hThread);
        }
#endif
        closesocket(connfd);
    }
}

#ifdef _WIN32
void subserver(Param *param)
{

    Header header(BUFFSIZE);
    RecvHeader(param->connfd, &header);
    std::string path(param->folder);
    if (path[path.length()-1]!=92 && path[path.length()-1]!=47){
#ifdef _WIN32
        path.append("\\");
#else
        path.append("/");
#endif
    }
    path.append(header.payloadInfo);
    header.setPayloadInfo(path);
    HeaderHandler(param->connfd, header);
    closesocket(param->connfd);
}
#endif

void HeaderHandler(SOCKET connfd, Header &header)
{
    if (header.payloadFlag & FLAG_FILE){
        RecvFile(connfd, header.payloadSize, header.payloadInfo);
        fprintf(stderr, "Filed received : \n%s\n", header.payloadInfo);
    }else{
        char *text = (char *)malloc((header.payloadSize+10) * sizeof(char));
        RecvByLength(connfd, header.payloadSize, text);
        text[header.payloadSize] = 0;
        fprintf(stderr, "Text received : \n%s\n", text);
        free(text);
    }
}
