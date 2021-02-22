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
	if ((fp = fopen(path, "r+t")) == NULL){
		err_exit("failed to open file to get lenght");
	}
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fclose(fp);
	return length;
}