/*
 * transferstuff.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "transferstuff.h"

int RecvHeader(int sockfd, Header *header){
	char buf[15];
	int rc, cnt=0;
	while((rc = read(sockfd, buf+cnt, H_LEN-cnt)) > 0){
		cnt += rc;
		if (cnt == H_LEN) break;
	}
	if (rc < 0){
		printf("error receiving header, read return negative\n");
		exit(0);
	}
	if (cnt != H_LEN){
		printf("error receiving header, lenght not match\n");
		exit(0);
	}
	memcpy(header, buf, H_LEN);
	RecvText(sockfd, header->length-H_LEN, header->payloadInfo);
	return 0;
}

int SendHeader(int sockfd, Header *header){
	write(sockfd, header, H_LEN);
	SendText(sockfd, header->length, header->payloadInfo);
	return 0;
}

int RecvText(int sockfd, int len, char *des){
	int rc, cnt=0;
	while((rc = read(sockfd, des+cnt, len-cnt>MAXLINE?MAXLINE:len-cnt)) > 0){
		cnt += rc;
	}
	if (rc == -1){
		//error code here
	}
	if (cnt <len){
		//error code here
	}
	return 0;
}

int SendText(int sockfd, int len, char *sou){
	int rc,i;
	for (i=0; i<len; i+=rc){
		rc = write(sockfd, sou+i, len-i>MAXLINE?MAXLINE:len-i);
		if (rc < 0){
			printf("error send text, write return negative\n");
		}
	}
	return 0;
}

int RecvFile(int sockfd, int len, char *path){
	FILE *fp;
	if ((fp = fopen(path, "wb")) == NULL){
		printf("Output file opened error before receiving\n");
		exit(0);
	}
	char *buf;
	buf = (char*)malloc((MAXLINE+10) * sizeof(char));
	int rc, cnt;
	while((rc = read(sockfd, buf, len-cnt>MAXLINE?MAXLINE:len-cnt))){
		cnt += rc;
		fwrite(buf, rc, 1, fp);
	}
	if (rc < 0){
		printf("File receive error, read return negative\n");
	}
	if (cnt <len){
		printf("File receive error, length not match\n");
		exit(0);
	}
	fclose(fp);
	return 0;
}

int SendFile(int sockfd, char *path){
	char *buf;
	buf = (char *)malloc((MAXLINE+10) * sizeof(char));
	FILE *fp;
	if ((fp = fopen(path, "wb")) == NULL){
		printf("File open error when send\n");
		//error code here
		exit(0);
	}
	int file_length = GetFileLength(path);
	int willsend,rc,i;
	for (i=0; i<file_length; i+=rc){
		willsend = file_length-i;
		if (willsend > MAXLINE) willsend = MAXLINE;
		rc = fread(buf, willsend, 1, fp);
		if (rc < 0){
			printf("File read error when send\n");
			exit(0);
		}
		if (rc < willsend) willsend = rc;
		int cnt = 0;
		while((rc = write(sockfd, buf+cnt, rc)) > 0){
			cnt += rc;
			if (cnt >= willsend) break;
		}
		if (rc < 0){
			printf("File send error, write return negative\n");
			exit(0);
		}
		if (cnt != willsend){
			printf("File send error, length not match\n");
			exit(0);
		}
	}
	fclose(fp);
	return 0;
}