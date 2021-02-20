#include "networkpacket.h"

Header::Header(int content_length=STRLEN){
  content = (char*)malloc(content_length * sizeof(char));
  length = content_length+6;
}

Header::~Header(){
  free(content);
}

void Header::setContent(char *str){
  strcpy(content, str);
}

void Header::setContent(std::string &str){
  strcpy(content, str.c_str());
}

Payload::Payload(int payloadInfo_size=STRLEN){
  payloadInfo = (char*)malloc(payloadInfo_size * sizeof(char));
}

Payload::~Payload(){
  free(payloadInfo);
}
void Payload::setPayloadInfo(char *info){
  strcpy(payloadInfo, info);
}
void Payload::setPayloadInfo(std::string& info){
  strcpy(payloadInfo, info.c_str());
}