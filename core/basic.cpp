#include "basic.h"

int Socket(int __domain, int __type, int __protocol){
    return socket(__domain, __type, __protocol);
}

int Bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len){
    return bind(__fd, __addr, __len);
}

int Connect(int __fd, __SOCKADDR_ARG __addr, socklen_t __len){
    return connect(__fd, __addr, __len);
}

int Accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len){
    return accept(__fd, __addr, __addr_len);
}