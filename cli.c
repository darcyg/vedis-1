/* 
vedis cli

gcc -W -Wall -O2 cli.c vedis.c -o cli
taka@cmwang.net 20140414

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vedis.h"

#ifdef OPENWRT
    #ifdef VOLATILE
        #define db "/tmp/db.br"
    #else
        #define db "/etc/config/db.br"
    #endif
#else //arm
    #ifdef VOLATILE
        #define db "/dev/shm/db.br"
    #else
        #define db "/etc/db.br"
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
    //printf("%s\n", db);

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
    rc = vedis_exec_result(pStore,&pResult);
    if ( rc != VEDIS_OK )
    {
        printf("err\n");
        return -1;
    }
    else
    {
        if ( vedis_value_is_array(pResult) )
        {
            /* Iterate over the elements of the returned array */
            vedis_value *pEntry;
            //puts("Array entries:");
            while ((pEntry = vedis_array_next_elem(pResult)) != 0 )
            {
                const char *zEntry;
                /* Cast to string and output */
                zEntry = vedis_value_to_string(pEntry, 0);
                
                if (strlen(zEntry) == 0)
                {
                    printf("null\n");
                }
                else
                {
                    printf("%s\n", zEntry);
                }
            }
        } 
        else
        {
            const char *zResponse;
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
    }
    vedis_close(pStore);
    return 0;
}
