#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "jsonxml.h"
#include "strTools.h"


char* json2xml(JSON j){
    switch( j->type) {
    case NULLTYPE:
        return xml_null();
    case BOOLTYPE:
        return xml_bool(j->bVal);
    case STRINGTYPE:
        return xml_string(j->sVal);
    case INTTYPE:
        return xml_int(j->iVal);
    case FLOATTYPE:
        return xml_float(j->fVal);
    case OBJECTTYPE:
        return xml_object(j->oVal);
    case ARRAYTYPE:
        return xml_array(j->aVal);
    default:
        return NULL;
    }
}

char *xml_null() {
    return strdup("<null />");
}

char *xml_bool( bool b){
    if(b){
        return strdup("<bool>true</bool>");
    } else {
        return strdup("<bool>false</bool>");
    }
}

char *xml_string(char *s){
    //allocate enough memory for the result
    //the 18 is the the length of the <string></string> 
    //plus the null character
    size_t length=strlen(s)+18;
    char *result = (char *)calloc(length,sizeof(char));
    snprintf(result,length,"<string>%s</string>",s);
    return result;
}

char *xml_int(int i){
    const length=128;
    char buffer[length];
    snprintf(buffer,length,"<number>%d</number>",i);
    return strdup(buffer);
}

    
        
char *xml_float(double d){
    const length=128;
    char buffer[length];
    snprintf(buffer,length,"<number>%G</number>",d);
    return strdup(buffer);
}

char *xml_array(JSON_array a){
    JSON_array curr;
    size_t length=128;
    char *buffer=(char *)malloc(length); //allocate some initial memory, safe_cat could make this bigger
    *buffer=0; //make it an empty string
    char *temp;
    safe_cat(&buffer,&length,"<array>");
    curr = a;
    while(*curr) {
        temp = json2xml(*curr);
        safe_cat(&buffer,&length,temp);
        free(temp); //free the memory allocated during json2xml
        ++curr; // move to the next element
    }
    
    safe_cat(&buffer,&length,"</array>");
}

char *xml_object(JSON_object o){
    size_t length=128;
    char *buffer=(char *)malloc(length);
    *buffer=0; //make the string zero length
    safe_cat(&buffer,&length,"<object>");
    xml_object_walk(o,&buffer,&length);
    safe_cat(&buffer, &length,"</object>");
}

void xml_object_walk(JSON_object o, char **buffer, size_t *length){
    char *valueString;
    if(! o) {
        return;  // return once we reach end points
    }
    xml_object_walk(o->left,buffer,length);

    valueString = json2xml(o->value);
    safe_cat(buffer,length, "<");
    safe_cat(buffer,length, o->key);
    safe_cat(buffer,length, ">");
    safe_cat(buffer,length, valueString);
    safe_cat(buffer, length, "</");
    safe_cat(buffer, length, o->key);
    safe_cat(buffer, length, ">");

    free(valueString);
    xml_object_walk(o->right,buffer,length);

}

