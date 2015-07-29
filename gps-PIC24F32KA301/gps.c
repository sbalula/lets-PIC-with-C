#include <p24F32KA301.h>
#include <stdio.h>
#include <string.h>
#include "uart2.h"
#include "gps.h"
#include "delays.h"

gpsdata gps, temp;

int wait_for_gps(char * thing) {
    int sizeofthing = strlen(thing);
    int i;

    for (i = 0; i < 80; ++i) {
        if (!strncmp(RXbuffer2 + i, thing, sizeofthing)) {
            return 0;
        }
    }
    return 1;
}

