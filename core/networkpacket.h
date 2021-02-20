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
	unsigned int  length;
	unsigned char version;
	unsigned char payloadFlag;

	unsigned int payloadSize;
	char *payloadInfo;

	Header(int payloadInfo_lenght=STRLEN);
	~Header();

	void setPayloadInfo(char *str);
	void setPayloadInfo(std::string &str);

	void setPayloadSize(int len);

	void attachFile(char *path);
	void attachFile(std::string& path);
	 
	void attachText(char *content);
	void attachText(std::string& content);

};

#endif // _NETWORKPACK_H