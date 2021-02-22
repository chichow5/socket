#include "core/basic.h"
#include "core/bridge.h"
#include "core/networkpacket.h"
#include "core/transferstuff.h"
#include "core/debug.h"
#include <sys/wait.h>

char ip[20];
int port;
char buf[BUFFSIZE];

void server();
void client();

int main(int args, char **argv){
	FILE *fp;
	if ((fp = fopen("config", "r")) == NULL){
		err_exit("please create the config file to specify ip and port!");
	}
	fscanf(fp,"%s%d",ip, &port);
	fclose(fp);

	if(args == 1) return 0;
	if (strcmp(argv[1], "s") == 0){
		server();
	}else if (strcmp(argv[1], "c") == 0){
		client();
	}
	return 0;
}
void server(){
	int     listenfd, connfd;
	int     childpid;

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
		close(connfd);
	}
}
void client(){
	printf("------> send message to %s:%d <------\n",ip,port);
	struct sockaddr_in servaddr;
	int sockfd;
	pid_t chilpid, status;
	Header header(MAXLINE);	
	char in[20];
	for( ; ; ){
		std::cin>>in;
		header.setPayloadInfo(in);
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
	}
}