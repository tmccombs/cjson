#include "pyjson.h"

#include "parse.h"


static PyObject *SyntaxError;


static PyObject *
cjson_parse(PyObject *self, PyObject *args)
{
    const char *json_string;
    JSON parse_result;
    PyObject *pyResult;

    if (! PyArg_ParseTuple(args, "s", &json_string))
        return NULL;
    parse_result =  json_parse_str(json_string);
    pyResult = JSON2PyObject(parse_result);
    if(! pyResult ) {
        PyErr_SetString(SyntaxError,"Syntax Error");
        return NULL;
    }
    json_free(parse_result);
    return pyResult;
}

static PyObject *
JSON2PyObject( JSON j) 
{
    if(! j) {
        return NULL;
    }
    switch( j->type) {
        case NULLTYPE:
            Py_RETURN_NONE;
        case BOOLTYPE:
            return PyBool_FromLong(j->bVal);
        case STRINGTYPE:
            return PyUnicode_FromString(j->sVal);
        case INTTYPE:
            return PyLong_FromLong(j->iVal);
        case FLOATTYPE:
            return PyFloat_FromDouble(j->fVal);
        case OBJECTTYPE:
            return jObj2PyDict(j->oVal);
        case ARRAYTYPE:
            return jArr2PyArr(j->aVal);
        default:
            return NULL;
    }
}

static PyObject *
jObj2PyDict(JSON_object o)
{
    PyObject *result;

    result=PyDict_New();
    
    walk_object2PyDict(o,result);

    return result;
}

static void
walk_object2PyDict(JSON_object o, PyObject *dict)
{
    if(! o ) {
        return;
    }
    walk_object2PyDict(o->left, dict);
    PyDict_SetItemString(dict,o->key,JSON2PyObject(o->value));
    walk_object2PyDict(o->right, dict);
}

static PyObject *
jArr2PyArr(JSON_array a)
{
    JSON_array curr;
    PyObject *result;

    result = PyList_New(0);
    curr=a;
    while(*curr) {
        PyList_Append(result,JSON2PyObject(*curr));
        ++curr;
    }
    return result;
}



static PyMethodDef CjsonMethods[] = {
    {"parse", cjson_parse, METH_VARARGS, "Parse a JSON string"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef cjsonmodule = {
    PyModuleDef_HEAD_INIT,
    "cjson", //name of module
    "Parse JSON strings to python objects", //docstring
    -1,
    CjsonMethods
};

PyMODINIT_FUNC
PyInit_cjson(void)
{
    PyObject *m;
    SyntaxError = PyErr_NewException("cjson.SyntaxError",NULL,NULL);
    m =  PyModule_Create(&cjsonmodule);
    if ( m == NULL || SyntaxError == NULL)
        return NULL;
    PyModule_AddObject(m,"SyntaxError",SyntaxError);
    return m;

}
