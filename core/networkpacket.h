/*
 * networkpacket.h
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#ifndef _NETWORKPACK_H
#define _NETWORKPACK_H 1

#define STRLEN 1024
#define H_LEN 10

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include "bridge.h"

struct Header{
	int  length;
	int  payloadSize;
	char version;
	char payloadFlag;

	char *payloadInfo;

	Header(int infoLen=0);
	~Header();

	void setPayloadInfo(char *str);
	void setPayloadInfo(std::string &str);

	void setPayloadSize(int len);

	void attachFile(char *path);
	void attachFile(std::string& path);
	 
	void attachText(char *content);
	void attachText(std::string& content);

	void show();
};

#endif // _NETWORKPACK_H