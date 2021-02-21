/*
 * transferstuff.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "transferstuff.h"

void RecvByLength(int connfd, int len, void *des){
	char *recv_buff=(char*)des;
	int remaining = len;
	int received = 0;
	int result = 0;
	while(remaining > 0){
		result = read(connfd, recv_buff+received, remaining>MAXLINE?MAXLINE:remaining);
		if (result > 0){
			remaining -= result;
			received += result;
		}else if (result == 0){
			printf("Error remote close before receiving all data\n");
			break;
		}else{
			printf("Error with read");
			break;
		}
	}
}

void SendByLength(int connfd, int len, void *sou){
	char *tosend = (char*)sou;
	int remaining = len;
	int sent = 0;
	int result = 0;
	while(remaining > 0){
		result = write(connfd, tosend+sent, remaining>MAXLINE?MAXLINE:remaining);
		if (result > 0){
			remaining -= result;
			sent += result;
		}else if (result < 0){
			printf("Error write\n");
			break;
		}
	}
}

int RecvHeader(int sockfd, Header *header){
	RecvByLength(sockfd, H_LEN, header);
	RecvByLength(sockfd, header->length-H_LEN, header->payloadInfo);
	return 0;
}

int SendHeader(int sockfd, Header *header){
	SendByLength(sockfd, H_LEN, header);
	SendByLength(sockfd, header->length-H_LEN, header->payloadInfo);
	return 0;
}

int SendText(int sockfd, int len, char *sou){
	SendByLength(sockfd, len, sou);
}

int RecvText(int sockfd, int len, char *des){
	RecvByLength(sockfd, len, des);
}

int SendFile(int sockfd, char *path){
	FILE *fp;
	if ((fp = fopen(path, "rb")) == NULL){
		printf("File open error when send\n");
		//error code here
		exit(0);
	}

	char *buf;
	buf = (char *)malloc((MAXLINE+10) * sizeof(char));

	int file_length = GetFileLength(path);
	int willsend, rc,i;

	for (i=0; i<file_length; i+=MAXLINE){
		willsend = file_length-i;
		if (willsend > MAXLINE) willsend = MAXLINE;
		if ((rc = fread(buf, willsend, 1, fp)) < 0){
			printf("File read error when sending\n");
			exit(0);
		}
		//if (rc == 0) break;
		int cnt = 0;
		while((rc = write(sockfd, buf+cnt, willsend-cnt)) > 0){
			if (rc < 0) break;
			cnt += rc;
			if (cnt >= willsend) break;
		}
		if (rc < 0){
			printf("File send error, write return negative\n");
			exit(0);
		}
		if (cnt < willsend){
			printf("File send error, length too short\n");
			exit(0);
		}
	}
	fclose(fp);
	return 0;
}

int RecvFile(int sockfd, int len, char *path){
	FILE *fp;
	if ((fp = fopen(path, "w")) == NULL){
		printf("Output file opened error before receiving\n");
		exit(0);
	}
	char *buf;
	buf = (char*)malloc((MAXLINE+10) * sizeof(char));
	int rc, cnt=0;
	while((rc = read(sockfd, buf, MAXLINE)) > 0){
		cnt += rc;
		if (cnt > len){
			printf("File receiving error, length overflow\n");
			exit(0);
		}
		fwrite(buf, rc, 1, fp);
		if (cnt == len) break;
	}
	if (rc < 0){
		printf("File receive error, read return negative\n");
	}
	if (cnt != len){
		printf("File receive error, length not match\n");
		printf("\tgot:%d, expected:%d\n",cnt, len);
		exit(0);
	}
	fclose(fp);
	return 0;
}
