/*
 * transferstuff.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "transferstuff.h"

int ReadByLength(int sockfd, int len, void *item){
	int rc, cnt;
	while((rc = read(sockfd, item+cnt, len-cnt>MAXLINE?MAXLINE:len-cnt))){
		cnt += rc;
	}
	if (cnt <len){
		//error code here
	}
}

int ReadToFile(int sockfd, int len, char *path){
	FILE *fp;
	if ((fp = fopen(path, "wb")) == NULL){
		//error code here
		exit(0);
	}
	char *buf;
	buf = (char*)malloc((MAXLINE+10) * sizeof(char));
	int rc, cnt;
	while((rc = read(sockfd, buf, len-cnt>MAXLINE?MAXLINE:len-cnt))){
		cnt += rc;
		fwrite(buf, rc, 1, fp);
	}
	if (cnt <len){
		//error code here
	}

}