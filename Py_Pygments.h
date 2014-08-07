#include<Python/Python.h>

PyObject *pyg_mod_pygments, *pyg_mod_formatters, *pyg_mod_lexers, *pyg_mod_styles; /** Modules **/

int initialize_python_and_pygments_modules();
PyObject* get_function_from_module(PyObject*, char*);
