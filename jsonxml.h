#ifndef JSONXML_H
#define JSONXML_H

#include <stdlib.h>

#include "json_types.h"


char * json2xml(JSON j);

char *xml_null();
char *xml_bool(bool b);
char *xml_string(char *s);
char *xml_int(int i);
char *xml_float(double d);
char *xml_array(JSON_array a);
char *xml_object(JSON_object o);

void xml_object_walk(JSON_object o, char **buffer, size_t *length);



#endif
