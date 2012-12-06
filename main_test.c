#include <stdio.h>


#include "json_types.h"
#include "parse.h"
#include "jsonxml.h"


int main(int argc, char *argv[]){
    char *s;
    JSON j;
    j=json_parse_str("\"Hi\\nHow are you?\"");
    s=json2xml(j);

    printf("%s\n",s);
    
    free(s);
    json_free(j);
    return 0;

}
