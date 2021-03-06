/****************************************************************************************
*  Copyright 2012 Thayne McCombs
* 
*  This file is part of cjson.
*  
*      cjson is free software: you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation, either version 3 of the License, or
*      (at your option) any later version.
*  
*      cjson is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*  
*      You should have received a copy of the GNU General Public License
*      along with cjson.  If not, see <http://www.gnu.org/licenses/>.
*/

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
