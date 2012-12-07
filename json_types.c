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
#include "json_types.h"

#include <stdlib.h>
#include <string.h>





//start an empty JSON object i.e. NULL
//
JSON_object json_new_object() { return NULL; }

//create a key-value pair that is a JSON object
//and can be extended by more pairs
JSON_obj_node *json_make_pair( char *key, JSON value) {
    JSON_object result = (JSON_object) malloc(sizeof(JSON_obj_node));
    if(!result) return NULL;
    result->key=strdup(key);
    result->value=value;
    result->left=NULL;
    result->right=NULL;

    return result;
}

void json_object_add_pair(JSON_object *obj, JSON_obj_node *pair) {
    if(!(*obj)) {
        *obj = pair;
        return;
    }
    if( strcmp(pair->key,(*obj)->key) < 0 ) {
        json_object_add_pair(&(*obj)->left,pair);
    } else {
        json_object_add_pair(&(*obj)->right,pair);
    }
}


//get the value that corresponds to the give key from the 
//JSON object (i.e. the hash list
JSON json_object_get(JSON_object object,char *key) {
    if(! object) {
        return NULL;
    }
    int cmp = strcmp(object->key,key);
    if( cmp == 0 ){
        return object->value;
    } else if( cmp < 0 ) {
        return json_object_get(object->left,key);
    } else {
        return json_object_get(object->right,key);
    }
}

void json_object_set(JSON_object *object, char *key, JSON value) {
    if(! (*object) ){
        *object = json_make_pair(key,value);
        return;
    }
    int cmp = strcmp(key,(*object)->key);
    if( cmp == 0 ) {
        (*object)->value = value;
    } else if( cmp < 0 ) {
        json_object_set(&(*object)->left,key,value);
    } else {
        json_object_set(&(*object)->right,key,value);
    }
}



/** Functions to construct a json object from each possible type **/

/* the null object (we only need one of them) */

struct JSON_node _json_null_value = { NULLTYPE, {0}};
JSON json_null(){
   return &_json_null_value; //set to the address of the null value
}

bool json_is_null(JSON j){
    return j->type == NULLTYPE;
}

JSON json_int(int i) {
    JSON result = (JSON)malloc(sizeof(JSON_node));
    if(! result) return NULL;
    
    result->type=INTTYPE;
    result->iVal=i;
    return result;
}

JSON json_bool(bool b) {
    JSON result = (JSON)malloc(sizeof(JSON_node));
    if(! result) return NULL;
    
    result->type=BOOLTYPE;
    result->bVal=b;
    return result;
}

JSON json_float(double d) {
    JSON result=(JSON)malloc(sizeof(JSON_node));
    if(! result) return NULL;

    result->type=FLOATTYPE;
    result->fVal=d;
    return result;
}


JSON json_string(char *s) {
    JSON result=(JSON)malloc(sizeof(JSON_node));
    if(! result) return NULL;

    result->type=STRINGTYPE;
    result->sVal=s;
    return result;
}


JSON json_array(JSON_array a) {
    JSON result=(JSON)malloc(sizeof(JSON_node));
    if(! result) return NULL;

    result->type=ARRAYTYPE;
    result->aVal=a;
    return result;
}


JSON json_object(JSON_object o) {
    JSON result=(JSON)malloc(sizeof(JSON_node));
    if(! result) return NULL;

    result->type=OBJECTTYPE;
    result->oVal=o;
    return result;
}


void json_free(JSON j){
    if(j->type == ARRAYTYPE) {
        json_array_free(j->aVal);
    } else if( j->type == OBJECTTYPE) {
        json_object_free(j->oVal);
    } else if ( j-> type == NULLTYPE) {
        return;
    }
    free(j);
}

void json_array_free(JSON_array a){
    JSON *curr=a;
    while(*curr) {
        json_free(*(curr++));
    }
    free(a);
}

void json_object_free(JSON_object o){
    if(! o) {
        return;
    }
    json_object_free(o->left);
    json_object_free(o->right);
    free(o->key); 
    json_free(o->value);
    free(o);
}


/**
 * walk over a JSON object and call the walker function on each object
 * It passes a pointer to the value, so the function can change the 
 * value in place if desired
 *
 * The payload is passed to the walker function at each call, this can be used to
 * pass additional information to the function, or for the function to store information
 * in a reentrant manner
 */
void json_walk_object(JSON_object obj, json_objWalker_t walker, void *payload)
{

    if( ! obj ){
        return;  //return if it is a null object
    }

    json_walk_object(obj->left, walker,payload);

    walker(obj->key, &(obj->value), payload);

    json_walk_object(obj->right, walker,payload);
}

void json_walk_array(JSON_array arr, json_arrWalker_t walker, void *payload)
{
    while(*arr) {
        walker(arr,payload);
    }
}
