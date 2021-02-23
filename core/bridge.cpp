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
int ResolveFileName(const char *path){
	int i,len = strlen(path);
	for (i = len-1; i>=0; i--){
		if (path[i] == 92 || path[i] == 47) return i+1;
		//92 -> \ 47 -> /
	}
	return 0;
}