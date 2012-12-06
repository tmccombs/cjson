
#include <stdlib.h>
#include <string.h>

#include "strTools.h"


//safely concatenat src onto dest, reallocating more memory if necessary.
//length is the number of chars currently in dest
//both dest and length are modified in place if the
//memory is reallocated
char *safe_cat(char **dest, size_t *length, char *src){
    size_t dest_l = strlen(*dest), src_l = strlen(src);
    if( dest_l + src_l + 1 > *length) {
        *length *= 2;
        *dest = realloc(*dest,*length*sizeof(char));
    }
    return strcat(*dest,src);
}
