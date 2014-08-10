#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include <Python/Python.h>

SV* create_pl_string_from_py_string(PyObject*);
PyObject* get_function_object(PyObject*, char*);
PyObject* create_py_string_from_pl_string(SV*);
SV* value_from_hash(HV*, char*);
AV* get_list_of_keys(HV*);
PyObject* get_function_from_module(PyObject*, char*); 
PyObject* create_py_tuple(int, ...);
PyObject* create_py_dict(int, ...);
PyObject* create_py_filehandle(char*, char*);
PyObject* create_pyobject_from_sv(SV*);
PyObject* interpret_py_string(PyObject*);
int check_existence_of_hash_keys(HV*, int, ...);
