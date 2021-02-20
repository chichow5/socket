#ifndef _NETWORKPACK_H
#define _NETWORKPACK_H 1

#define STRLEN 1024

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>

struct Header{
  unsigned long long length;
  unsigned char version;
  unsigned char payloadFlag;
  char *content;

  Header(int content_lenght=STRLEN);
  ~Header();

  void setContent(char *str);
  void setContent(std::string &str);
};

struct Payload{
  unsigned long long payloadSize;
  char *payloadInfo;
  Payload(int payloadInfo_size=STRLEN);
  ~Payload();

  void setPayloadInfo(char *info);
  void setPayloadInfo(std::string& info);
};

#endif // _NETWORKPACK_H