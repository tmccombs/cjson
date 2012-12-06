
#include <stdlib.h>
#include <string.h>

#include "strTools.h"

#define SCAT_BUFFER_SIZE     512         // size to increase buffer by when we run out of length

//safely concatenat src onto dest, reallocating more memory if necessary.
//length is the number of chars currently in dest
//both dest and length are modified in place if the
//memory is reallocated
char *safe_cat(char **dest, size_t *length, char *src){
    size_t dest_l = strlen(*dest), src_l = strlen(src);
    if( dest_l + src_l + 1 > *length) {
        *length += SCAT_BUFFER_SIZE;
        *dest = realloc(*dest,*length*sizeof(char));
    }
    return strcat(*dest,src);
}
