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
