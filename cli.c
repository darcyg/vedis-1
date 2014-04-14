/* 

vedis cli
gcc -W -Wall -O2 cli.c vedis.c -o cli

taka@bandrich.com 20140414
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vedis.h"

#ifdef OPENWRT
    #ifdef VOLATILE
        #define db "/tmp/vol.db"
    #else
        #define db "/tmp/no-vol.db"
    #endif
#else //arm
    #ifdef VOLATILE
        #define db "/dev/shm/vol.db"
    #else
        #define db "/etc/no-vol.db"
    #endif
#endif

#define MAX_LEN 512

int main(int argc,char *argv[])
{
    char buffer[MAX_LEN];
    buffer[0] = 0;
    int offset = 0;
    while (argv++, --argc)
    {
        int toWrite = MAX_LEN - offset;
        int written = snprintf(buffer + offset, toWrite, "%s ", *argv);
        if (toWrite < written)
        {
            break;
        }
        offset += written;
    }
    //printf("%s\n", buffer);

    vedis *pStore;            /* Vedis handle */
    vedis_value *pResult;     /* Return value of the last executed command */
    int rc;
    rc = vedis_open(&pStore, db);
    if ( rc != VEDIS_OK )
    {
        printf("err\n");
        return -1;
    }
    
    vedis_exec(pStore,buffer,-1);
    /* Extract the return value of the last executed command (i.e. GET test) " */
    rc = vedis_exec_result(pStore,&pResult);
    if ( rc != VEDIS_OK )
    {
        printf("err\n");
        return -1;
    }
    else
    {
        const char *zResponse;
        /* Cast the vedis object to a string */
        zResponse = vedis_value_to_string(pResult,0);
        if (strlen(zResponse) == 0)
        {
            printf("null\n");
        } 
        else
        {
            printf("%s\n", zResponse); 
        }

    }
    vedis_close(pStore);
    return 0;
}