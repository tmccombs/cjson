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
#include <stdio.h>


#include "json_types.h"
#include "json.h"
#include "jsonxml.h"


void test_encoder(void);


int main(int argc, char *argv[]){
    char *s;
    JSON j;
    j=json_parse_str("\"Hi\\nHow are you?\"");
    s=json2xml(j);

    printf("%s\n",s);


    
    free(s);
    json_free(j);

    test_encoder();

    return 0;

}


void test_encoder(void)
{
    JSON j;
    char *s;
    j = json_parse_str("{\"name\":\"Thayne\",\"Languages\":[\"C\",\"Python\",\"c++\",4.5,2],\"nullVal\":null,\"young\":true}");

    printf("The json string (reencoded): \n\n");

    json_fencode(stderr, j);
    putchar('\n');

    json_free(j);
    return;

}
