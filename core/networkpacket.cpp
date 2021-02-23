/*
 * networkpacket.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "networkpacket.h"

Header::Header(int infoLen){
	length = H_LEN;
	version = 1;
	payloadFlag = FLAG_NONE;
	payloadSize = 0;
	if(infoLen == 0) payloadInfo = NULL;
	else{
		if ((payloadInfo = (char *)malloc((infoLen+10) * sizeof(char))) ==NULL){
			err_exit("failed to initial header");
		}
	}
}

Header::~Header(){
	free(payloadInfo);
}

void Header::setPayloadInfo(char *str){
	if (strlen(str) > MAXLINE){
		err_exit("string is longer than payloadInfo size!");
	}
	if(payloadInfo == NULL){
		if ((payloadInfo = (char *)malloc((strlen(str)+10) * sizeof(char))) ==NULL){
			err_exit("failed to initialize header.payloadInfo");
		}
	}
	int filename_start = ResolveFileName(str);
	strncpy(payloadInfo, str+filename_start, strlen(str)-filename_start);
	payloadInfo[strlen(str)-filename_start] = 0;
	length = H_LEN + strlen(str);
}

void Header::setPayloadInfo(std::string &str){
	if (str.length() > MAXLINE){
		err_exit("string is longer than payloadInfo size!");
	}
	if(payloadInfo == NULL){
		if ((payloadInfo = (char *)malloc((str.length()+10) * sizeof(char))) ==NULL){
			err_exit("failed to initial header.payloadInfo");
		}
	}
	int filename_start = ResolveFileName(str.c_str());
	strncpy(payloadInfo, str.c_str()+filename_start, str.length()-filename_start);
	payloadInfo[str.length()-filename_start] = 0;
	length = H_LEN + str.length();
}

void Header::setPayloadSize(int len, char flag){
	if (flag - FLAG_FILE > 0){
		err_exit("bad payload flag combination");
	}else if (flag == FLAG_CLIP){
		err_exit("bad payload flag combination");
	}else if (flag >= (1<<FLAG_NUM)){
		err_exit("bad payload flag combination");
	}
	payloadFlag = flag;
	payloadSize = len;
}

void Header::attachFile(char *path, char flag){
	setPayloadSize(GetFileLength(path), flag);
}

void Header::attachFile(std::string& path, char flag){
	setPayloadSize(GetFileLength(path.c_str()), flag);
}

void Header::attachText(char *content, char flag){
	setPayloadSize(strlen(content), flag);
}

void Header::attachText(std::string& content, char flag){
	setPayloadSize(content.length(), flag);
}

void Header::show(){
	printf("0x%x int  length       %d\n", &length, length);
	printf("0x%x int payloadSize   %d\n", &payloadSize, payloadSize);
	printf("0x%x char version      %d\n", &version, version); 
	printf("0x%x char payloadFlag  %d\n", &payloadFlag, payloadFlag);
	printf("0x%x char *payloadInfo %s\n", &payloadInfo, payloadInfo); 
}