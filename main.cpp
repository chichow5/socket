#ifndef _WIN32
#include "core/basic.h"
#include <sys/wait.h>
#else
#include "core/winbasic.h"
#endif
#include "core/bridge.h"
#include "core/networkpacket.h"
#include "core/transferstuff.h"
#include "core/debug.h"

char ip[20];
int port;
char buf[BUFFSIZE];

void server();
void client();

#ifdef _WIN32
HANDLE hMutex;

void subserver(SOCKET *connfd) {
	WaitForSingleObject(hMutex, INFINITE);
	printf("\n\e\[31m----->\e\[0mconnection from client...\n");

	Header header(BUFFSIZE);
	RecvHeader(*connfd, &header);
	header.show();
	if (header.payloadFlag) {
		RecvFile(*connfd, header.payloadSize, header.payloadInfo);
	}
	ReleaseMutex(hMutex);
}
void subclient(Header *header) {
	SOCKET sockfd;
	struct sockaddr_in servaddr;
	header->attachFile(header->payloadInfo);
	header->show();

	SetupClient(&servaddr, ip, port, &sockfd);
	
	WaitForSingleObject(hMutex, INFINITE);
	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

	SendHeader(sockfd, header);
	SendFile(sockfd, header->payloadInfo);

	printf("Sending Complete\n");
	close(sockfd);
	ReleaseMutex(hMutex);
}

#endif

int main(int args, char **argv){
	FILE *fp;
	if ((fp = fopen("config", "r")) == NULL){
		err_exit("please create the config file to specify ip and port!");
	}
	fscanf(fp,"%s%d",ip, &port);
	fclose(fp);

#ifdef _WIN32
	//³õÊ¼»¯ DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
	if(args == 1) return 0;
	if (strcmp(argv[1], "s") == 0){
		server();
	}else if (strcmp(argv[1], "c") == 0){
		client();
	}
#ifdef _WIN32
	WSACleanup();
#endif
	return 0;
}

void server(){
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

	printf("Start listening on port : %d\n",port);

	for( ; ; ){
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
#ifndef _WIN32
		if ((childpid = fork()) == 0){
			printf("\n\e\[31m----->\e\[0mconnection from client...\n");
			close(listenfd);

			Header header(BUFFSIZE);
			RecvHeader(connfd, &header);
			header.show();
			if (header.payloadFlag){
				RecvFile(connfd, header.payloadSize, header.payloadInfo);
			}
			close(connfd);
			exit(0);
		}
#else
		HANDLE hThread;
		if ((hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&subserver, &connfd, 0, NULL)) <= 0) {
			err_msg("failed to create sub thread");
		}
		if (hThread != 0) {
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		}
#endif
		close(connfd);
	}
}
void client(){
	printf("------> send message to %s:%d <------\n",ip,port);
#ifndef _WIN32
	struct sockaddr_in servaddr;
	SOCKET sockfd;
	pid_t chilpid;
	int status;
#endif
	Header header(MAXLINE);	
	char in[20];
	for( ; ; ){
		std::cin>>in;
		header.setPayloadInfo(in);
#ifndef _WIN32
		if ((chilpid = fork()) == 0){
			header.attachFile(in);
			header.show();

			SetupClient(&servaddr, ip, port, &sockfd);
			Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

			SendHeader(sockfd, &header);
			SendFile(sockfd, in);

			printf("Sending Complete\n");
			close(sockfd);
			exit(0);
		}
		if ((chilpid = wait(&status)) < 0){
			err_msg("bad wait with status: %d",status);
		}
#else
		HANDLE hThread;
		if ((hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&subclient, &header , 0, NULL)) <= 0) {
			err_msg("failed to create sub thread");
		}
		if (hThread != 0) {
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		}
#endif
	}
}