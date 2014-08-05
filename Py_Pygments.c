#include "Py_Pygments.h"

int initialize_python_and_pygments_modules() {
	if(Py_IsInitialized())
		return 1;

	Py_Initialize();
	pyg_mod_pygments = PyImport_ImportModule("pygments");
	pyg_mod_formatters = PyImport_ImportModule("pygments.formatters");
	pyg_mod_lexers = PyImport_ImportModule("pygments.lexers");
	pyg_mod_styles = PyImport_ImportModule("pygments.styles");
	if(pyg_mod_pygments == NULL || pyg_mod_formatters == NULL || pyg_mod_lexers == NULL || pyg_mod_styles)
		return 0;

	/** Success! **/
	return 1;
}

PyObject* get_function_from_module(PyObject* module, char* function_name) {
	return PyObject_GetAttrString(module, function_name);
}

PyObject* create_py_string_from_perl_string(SV* str) {

}

PyObject* create_lexer(HV* lexer) {
	PyObject_CallFunction(get_function_from_module(pyg_mod_lexer, "get_lexer_by_name"), "s", ---- options->{lexer}->{type});
}

PyObject* create_formatter(HV* formatter) {

}
