/*
 * winbasic.h
 * socket
 *
 * Created by Chi Chow on 2021-2-22
 *
*/

#include "winbasic.h"

void err_msg(const char* fmt, ...) {
	fprintf(stderr, "Error : %s ", strerror(errno));
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}

void err_exit(const char* fmt, ...) {
	fprintf(stderr, "Error : %s ", strerror(errno));
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

void SetupClient(struct sockaddr_in* servaddr, char* ip, int port, SOCKET* sockfd) {
	*sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	memset(servaddr, 0, sizeof(servaddr));
	servaddr->sin_family = AF_INET;
	servaddr->sin_port = htons(port);
	servaddr->sin_addr.s_addr = inet_addr(ip);
}

SOCKET Socket(int af, int type, int protocol) {
	SOCKET re;
	if ((re = socket(af, type, protocol)) < 0) {
		err_exit("failed to obtain socket descriptor");
	}
	return re;
}

int Bind(SOCKET s, const struct sockaddr* name, int namelen) {
	int re;
	if ((re = bind(s, name, namelen)) < 0) {
		err_exit("failed to bind socket descriptor and adress structure");
	}
	return re;
}

int Connect(SOCKET s, const struct sockaddr* name, int namelen) {
	int re;
	if ((re = connect(s, name, namelen)) < 0) {
		err_exit("failed to connect");
	}
	return re;
}

SOCKET Accept(SOCKET s, struct sockaddr* addr, int* addrlen) {
	SOCKET re;
	if ((re = accept(s, addr, addrlen)) < 0) {
		err_exit("failed to accept");
	}
	return re;
}
