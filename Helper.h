#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include <Python/Python.h>

SV* create_pl_string_from_py_string(PyObject* py_string);
PyObject* get_function_object(PyObject* module, char* function_name);
PyObject* create_py_string_from_pl_string(SV* str);
SV* value_from_hash(HV* hash, char* key);
AV* get_list_of_keys(HV* hash);
PyObject* get_function_from_module(PyObject*, char*); 
PyObject* create_py_tuple(int, ...);
PyObject* create_py_dict(int, ...);
