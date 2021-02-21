#include "debug.h"

void hexdump(void *item, int len){
    char *tmp = (char *)item;
    unsigned char t;
    printf("Hex Table");
    for (int i=0; i<len; i++){
        if (i%4 == 0) printf("\n0x%02x\t",i);
        else if(i%2 == 0) printf("  ");
        t = tmp[i];
        for (int i=7; i>=0; i--){
            printf("%d",(t&(1<<i))>0);
        }
        printf(" ");
    }
    puts("");
}