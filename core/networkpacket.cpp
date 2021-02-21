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
	payloadFlag = 0;
	payloadSize = 0;
	if(infoLen == 0) payloadInfo = NULL;
	else payloadInfo = (char *)malloc((infoLen+1) * sizeof(char));
}

Header::~Header(){
	free(payloadInfo);
}

void Header::setPayloadInfo(char *str){
	if(payloadInfo == NULL){
		payloadInfo = (char*)malloc((strlen(str)+10) * sizeof(char));
	}
	strcpy(payloadInfo, str);
	length = H_LEN + strlen(str);
}

void Header::setPayloadInfo(std::string &str){
	if(payloadInfo == NULL){
		payloadInfo = (char*)malloc((str.length()+10) * sizeof(char));
	}
	strcpy(payloadInfo, str.c_str());
	length = H_LEN + str.length();
}

void Header::setPayloadSize(int len){
	payloadFlag = 1;
	payloadSize = len;
}

void Header::attachFile(char *path){
	setPayloadSize(GetFileLength(path));
}

void Header::attachFile(std::string& path){
	setPayloadSize(GetFileLength(path.c_str()));
}

void Header::attachText(char *content){
	setPayloadSize(strlen(content));
}

void Header::attachText(std::string& content){
	setPayloadSize(content.length());
}
void Header::show(){
	printf("int  length       %d\n", length);
	printf("char version      %d\n", (int)version); 
	printf("char payloadFlag  %d\n", (int)payloadFlag);
	printf("int payloadSize   %d\n", payloadSize);
	printf("char *payloadInfo %s\n", payloadInfo); 
}