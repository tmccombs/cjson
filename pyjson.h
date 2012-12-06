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
#ifndef PYJSON_H
#define PYJSON_H

#include <Python.h>

#include "json_types.h"

static PyObject * cjson_parse(PyObject *self, PyObject *args);
static PyObject *JSON2PyObject(JSON j);
static PyObject * jObj2PyDict(JSON_object o);
static void walk_object2PyDict(JSON_object o, PyObject *dict);
static PyObject * jArr2PyArr(JSON_array);


#endif
