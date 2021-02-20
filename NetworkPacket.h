#include <cstdio>
#include <iostream>
using namespace std;

struct Header{
  unsigned long long length;
  unsigned char payloadFlag;
};

struct fileTransferJob{
  Header header;
  unsigned long long payloadSize;
  char **payloadTransferInfo;
};

struct FileTransferJob{
  Header header;
  unsigned long long payloadSize;
  char **payloadTransferInfo;
}
