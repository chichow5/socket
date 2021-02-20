/*
 * bridge.cpp
 * socket
 *
 * Created by Chi Chow on 2021-2-20
 *
*/

#include "bridge.h"

int GetFileLength(const char *path)
{
	FILE *fp;
	int length;
	if ((fp = fopen(path,"r+t")) != NULL){
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		fclose(fp);
	}
	return length;
}