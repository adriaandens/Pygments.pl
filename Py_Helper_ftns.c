#include "Py_Helper_ftns.h"

SV* create_pl_string_from_py_string(PyObject* py_string);
PyObject* get_function_object(PyObject* module, char* function_name) {
	return PyObject_GetAttrString(module, function_name);
}
PyObject* call_function(PyObject* function, ...);
