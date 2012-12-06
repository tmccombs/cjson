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
