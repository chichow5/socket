/*
 * transferstuff.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "transferstuff.h"

void RecvByLength(SOCKET connfd, int len, void *vptr){
	char *ptr=(char*)vptr;
	int nleft = len;
	int nread = 0;
	while(nleft > 0){
		if ((nread = recv(connfd, ptr, std::min(nleft, MAXLINE), MSG_WAITALL)) < 0){
			if (errno == EINTR) nread = 0;
			else{
				err_exit("failed to read from remote");
			}
		}else if (nread == 0){
			err_exit("read meet EOF");
		}
		nleft -= nread;
		ptr   += nread;
	}
}

void SendByLength(SOCKET connfd, int len, void *sou){
	char *ptr = (char*)sou;
	int nleft = len;
	int nsent = 0;
	while(nleft > 0){
		if ((nsent = send(connfd, ptr, std::min(nleft, MAXLINE), MSG_WAITALL)) < 0){
			if (errno == EINTR) nsent = 0;
			else{
				err_exit("failed to send to remote");
			}
		}else if (nsent == 0){
			err_msg("send return 0");
			break;
		}
		nleft -= nsent;
		ptr   += nsent;
	}
}

void RecvHeader(SOCKET sockfd, Header *header){
	RecvByLength(sockfd, H_LEN, header);
	RecvByLength(sockfd, header->length-H_LEN, header->payloadInfo);
	header->payloadInfo[header->length - H_LEN] = 0;
	//set char string end flag
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
	int nread = 0;
	int nleft = GetFileLength(path);
	if ((fp = fopen(path, "rb")) == NULL){
		err_exit("failed to open sending file, %s",path);
	}
	while(nleft > 0){
		if ((nread = fread(buf, sizeof(char), std::min(nleft, MAXLINE), fp)) < 0){
			err_exit("failed to read from file, %s",path);
		}else if (nread == 0){
			err_msg("no content read from file");
			break;
		}
		SendByLength(sockfd, nread, buf);
		nleft -= nread;
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
	int nleft = len;
	int nread = 0;
	while(nleft > 0){
		if ((nread = recv(sockfd, buf, std::min(nleft, MAXLINE), MSG_WAITALL)) < 0){
			if (errno == EINTR) nread = 0;
			else{
				err_exit("failed to read to write to file");
			} 
		}else if (nread == 0){
			err_msg("read meet EOF when receiving file");
			break;
		}
		if (nread == 0) continue;
		nleft -= nread;
		if (fwrite(buf, nread, 1, fp) < 0){
			err_exit("failed to write received buffer to file");
		}
	}
	free(buf);
	fclose(fp);
}
