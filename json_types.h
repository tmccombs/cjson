#ifndef JSON_TYPES_H
#define JSON_TYPES_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum { NULLTYPE, BOOLTYPE, STRINGTYPE, INTTYPE, FLOATTYPE, OBJECTTYPE, ARRAYTYPE } JSON_type;

struct JSON_node;
typedef struct JSON_node JSON_node;
struct JSON_obj_node;
typedef struct JSON_obj_node JSON_obj_node;

typedef JSON_node *JSON;
typedef JSON_obj_node *JSON_object;
typedef JSON *JSON_array; 

/** This is essentially a hash tree
 * left is less than, and right is greater than 
 */
struct JSON_obj_node {
    char *key;
    JSON value;
    JSON_object left;
    JSON_object right;

};



struct JSON_node {
    JSON_type type; //the type of the node

    //a union which contains the possible values
    union {
        double fVal;
        int iVal;
        bool bVal;
        char *sVal;
        JSON_object oVal;
        JSON_array aVal;
    };
};



JSON_object json_new_object(void);

JSON_obj_node *json_make_pair(char *key, JSON value);

void json_object_add_pair(JSON_object *obj, JSON_obj_node *pair);

JSON json_object_get(JSON_object object, char *key);
void json_object_set(JSON_object *object, char *key, JSON value);

JSON json_null(void);
JSON json_int(int i);
JSON json_bool(bool b);
JSON json_float(double d);
JSON json_string(char *s);
JSON json_array(JSON_array a);
JSON json_object(JSON_object o);

bool json_is_null(JSON j);

void json_free(JSON j);
void json_object_free(JSON_object o);
void json_array_free(JSON_array a);

#endif
