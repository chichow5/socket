#include <cstdio>
#include <iostream>
using namespace std;

struct Header{
  unsigned long long length;
  unsigned char payloadFlag;
};

struct Payload{
  Header header;
  unsigned long long payloadSize;
  char **payloadTranferInfo;
};