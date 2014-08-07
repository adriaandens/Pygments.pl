#include "Py_Helper_ftns.h"

SV* create_pl_string_from_py_string(PyObject* py_string) {
	char* str = PyBytes_AsString(py_string);
	return SvREFCNT_inc(newSVpvn(str, strlen(str)));
}

PyObject* get_function_object(PyObject* module, char* function_name) {
	return PyObject_GetAttrString(module, function_name);
}
