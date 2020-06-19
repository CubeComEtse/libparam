/*
 * File.c
 *
 * Created: 2020/05/27 10:43:30
 *  Author: Kolijn
 */

#include <errno.h>
#include <stdio.h>
#include <sys/unistd.h>
#include "serial_multiplexer.h"


int _write(int file, char *data, int len)
{
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }
    SERMUX_vTransmit(0, (uint8_t*) data, len);

    // Return bytes written - we don't know if serial tx works
    return len;
}

int _read(int file, char *data, int len){
    return 0;
}