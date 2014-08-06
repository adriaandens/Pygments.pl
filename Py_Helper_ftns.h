SV* create_pl_string_from_py_string(PyObject* py_string);
PyObject* get_function_object(PyObject* module, char* function_name);
PyObject* call_function(PyObject* function, ...);
