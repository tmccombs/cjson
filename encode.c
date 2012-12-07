

#include <stdio.h>

#include "json_types.h"

static  int fencode_object(FILE *fp, JSON_object obj);
static int fencode_array(FILE *fp, JSON_array arr);
static int objFencode_helper(FILE *fp, JSON_object obj);




// encode the json object and write to the file pointer
int json_fencode(FILE *fp, JSON json)
{
    if( ! json ){
        return -2;  // null pointer
    }

    switch ( json->type ) {
        case NULLTYPE:
            return fprintf(fp,"null");
        case BOOLTYPE:
            return fprintf(fp,json->bVal ? "true": "false");
        case STRINGTYPE:
            //TODO escape special characters
            return fprintf(fp,"\"%s\"", json->sVal);
        case INTTYPE:
            return fprintf(fp, "%d", json->iVal);
        case FLOATTYPE:
            //TODO make sure this outputs full precision
            return fprintf(fp, "%g", json->fVal);
        case OBJECTTYPE:
            return fencode_object(fp, json->oVal);
        case ARRAYTYPE:
            return fencode_array(fp, json->aVal);
        default:
            return -3;  // unrecognized type
    }

    fflush(fp);
}

int fencode_array(FILE *fp, JSON_array arr)
{
    int chars_written=1; // start with one for leading '['
    putc('[',fp);
    while( *arr ) { 
        chars_written += json_fencode(fp,*arr++); // encode the next element
        if( *arr) {
            // add a comma if there is another element
            putc(',',fp);
            chars_written++;
        }
    }
    putc(']',fp);
    chars_written++; 
    return chars_written;
}

int objFencode_helper(FILE *fp, JSON_object obj)
{
    int chars_written=0;
    if( ! obj) return 0;

    if( obj->left )
    {
        chars_written += objFencode_helper(fp, obj->left);
        putc(',',fp);
        chars_written++;
    }
    //TODO escape string
    chars_written += fprintf(fp, "\"%s\":", obj->key);
    chars_written += json_fencode(fp, obj->value);
    if( obj->right)
    {
        putc(',',fp);
        chars_written++;
        chars_written += objFencode_helper(fp, obj->right);
    }
    return chars_written;

}

int fencode_object(FILE *fp, JSON_object obj)
{
    int chars_written =1;
    putc('{',fp);
    chars_written += objFencode_helper(fp, obj);

    putc('}',fp);
    return chars_written+1;
}

