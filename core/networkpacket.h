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

#define FLAG_NONE 0		//无payload标志
#define FLAG_FILE 1<<0	//文件标志
#define FLAG_TEXT 1<<1	//文本标志
#define FLAG_CLIP 1<<2	//剪贴板标志
#define FLAG_NUM 3

#include "bridge.h"
#ifndef _WIN32
#include "basic.h"
#else
#include "winbasic.h"
#endif

struct Header{
	int  length;
	int  payloadSize;
	char version;
	char payloadFlag;

	char *payloadInfo;

	Header(int infoLen=MAXLINE);
	~Header();

	void setPayloadInfo(char *str);
	void setPayloadInfo(std::string &str);

	void setPayloadSize(int len, char flag);

	void attachFile(char *path);
	void attachFile(std::string& path);
	 
	void attachText(char *content, char flag);
	void attachText(std::string& content, char flag);

	void show();
};

#endif // _NETWORKPACK_H