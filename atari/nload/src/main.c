/**
 * @brief   Network Load File
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license gpl v. 3, see LICENSE for details.
 */

#include <atari.h>
#include <string.h>
#include <stdbool.h>
#include <fujinet-network.h>
#include "cio.h"
#include "conio.h"
#include "put_error.h"

extern unsigned char _LMARGN_save;
extern unsigned char _LSTACK_RUN__[];
extern unsigned char _LSTACK_LOAD__[];
extern unsigned char _LSTACK_SIZE__[];
extern unsigned char _LOADER_RUN__[];
extern unsigned char _LOADER_LOAD__[];
extern unsigned char _LOADER_SIZE__[];

extern void load_app(void);

void load(void)
{
    network_open((char *)OS.lbuff,4,0);

    if (OS.dvstat[3]>1)
    {
        memset(OS.lbuff,0x00,sizeof(OS.lbuff));
        put_error(OS.dvstat[3]);

        // This is silly, but...
        memset(&OS.lbuff[5],0x00,1);
        
        print("ERROR-   ");
        print((char *)&OS.lbuff[1]);
        while(1);
        return;
    }

    // Move loader into low memory
    memcpy(_LSTACK_RUN__, _LSTACK_LOAD__, _LSTACK_SIZE__);
    memcpy(_LOADER_RUN__, _LOADER_LOAD__, _LOADER_SIZE__);

    // load the program
    load_app();
}

bool get_filename(void)
{
    unsigned char *s = &OS.lbuff[0];
    unsigned char *d = &OS.lbuff[3];
    
    memset(OS.lbuff,0,sizeof(OS.lbuff));

    OS.lmargn = _LMARGN_save; // cc65 monkeys with this. stop it.
    
    print("NETWORK LOAD FROM WHAT FILE?\x9B");
    get_line((char *)OS.lbuff,sizeof(OS.lbuff));

    if (OS.lbuff[0]==0x9B)
        return false;

    if (OS.lbuff[0]=='N' && OS.lbuff[1] == ':')
        return true;

    if (OS.lbuff[0]=='N' && OS.lbuff[2] == ':')
        return true;

    // We only got a filename, shift devicespec over and stick N1: there.

    memmove(d,s,124);
    OS.lbuff[0] = 'N'; OS.lbuff[1] = '1'; OS.lbuff[2] = ':';

    // We're good.
    return true;
}

void main(void)
{
    if (get_filename())
        load();
}
