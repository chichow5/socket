/*
 * transferstuff.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "transferstuff.h"

void RecvByLength(SOCKET connfd, int len, void *des){
	char *recv_buff=(char*)des;
	int remaining = len;
	int received = 0;
	int result = 0;
	while(remaining > 0){
#ifndef _WIN32
		result = read(connfd, recv_buff+received, remaining>MAXLINE?MAXLINE:remaining);
#else
		result = recv(connfd, recv_buff + received, remaining > MAXLINE ? MAXLINE : remaining, NULL);
#endif
		if (result > 0){
			remaining -= result;
			received += result;
		}else if (result == 0){
			err_exit("remote close before receiving all data");
			break;
		}else{
			err_exit("failed to read from remote");
			break;
		}
	}
}

void SendByLength(SOCKET connfd, int len, void *sou){
	char *tosend = (char*)sou;
	int remaining = len;
	int sent = 0;
	int result = 0;
	while(remaining > 0){
#ifndef _WIN32
		result = write(connfd, tosend+sent, remaining>MAXLINE?MAXLINE:remaining);
#else
		result = send(connfd, tosend + sent, remaining > MAXLINE ? MAXLINE : remaining, NULL);
#endif
		if (result > 0){
			remaining -= result;
			sent += result;
		}else if (result < 0){
			err_exit("failed to write to remote");
			break;
		}
	}
}

void RecvHeader(SOCKET sockfd, Header *header){
	RecvByLength(sockfd, H_LEN, header);
	RecvByLength(sockfd, header->length-H_LEN, header->payloadInfo);
}

void SendHeader(SOCKET sockfd, Header *header){
	SendByLength(sockfd, H_LEN, header);
	SendByLength(sockfd, header->length-H_LEN, header->payloadInfo);
}

void SendText(SOCKET sockfd, int len, char *sou){
	SendByLength(sockfd, len, sou);
}

void RecvText(SOCKET sockfd, int len, char *des){
	RecvByLength(sockfd, len, des);
}

void SendFile(SOCKET sockfd, char *path){
	FILE *fp;
	char *buf;
	if ((buf = (char*)malloc((MAXLINE+10) * sizeof(char))) == NULL){
		err_exit("failed to ask for memory for sending buff");
	}
	int have_read = 0;
	int remaining = GetFileLength(path);
	if ((fp = fopen(path, "rb")) == NULL){
		err_exit("failed to open file, %s",path);
	}
	while(remaining > 0){
		have_read = fread(buf, sizeof(char), remaining>MAXLINE?MAXLINE:remaining, fp);
		if (have_read < 0){
			err_exit("failed to read from file, %s",path);
		}
		if (have_read == 0){
			err_exit("no content read from file");
		}
		SendByLength(sockfd, have_read, buf);
		remaining -= have_read;
	}
	fclose(fp);
	free(buf);
}

void RecvFile(SOCKET sockfd, int len, char *path){
	FILE *fp;
	if ((fp = fopen(path, "wb")) == NULL){
		err_exit("failed to create file, %s",path);
	}
	char *buf;
	if ((buf = (char*)malloc((MAXLINE+10) * sizeof(char))) == NULL){
		err_exit("failed to ask for memory for receiving buff");
	}
	int remaining = len;
	int result = 0;
	while(remaining > 0){
#ifndef _WIN32
		result = read(sockfd, buf, remaining>MAXLINE?MAXLINE:remaining);
#else
		result = recv(sockfd, buf, remaining > MAXLINE ? MAXLINE : remaining, NULL);
#endif
		if (result > 0){
			remaining -= result;
			if (fwrite(buf, result, 1, fp) < 0){
				err_exit("failed to write received buffer");
			}
		}else if (result == 0){
			err_exit("socket closed before receiving all data");
		}else{
			err_exit("failed to read when receiving");
		}
	}
	free(buf);
	fclose(fp);
}
