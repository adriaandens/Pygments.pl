#include "Py_Pygments.h"
#include "Logger.h"

int initialize_python_and_pygments_modules() {
	if(Py_IsInitialized()) {
		logger("Python has already been initialized.\n");
		return 1;
	}

	Py_Initialize();
	pyg_mod_pygments = PyImport_ImportModule("pygments");
	pyg_mod_formatters = PyImport_ImportModule("pygments.formatters");
	pyg_mod_lexers = PyImport_ImportModule("pygments.lexers");
	pyg_mod_styles = PyImport_ImportModule("pygments.styles");
	if(pyg_mod_pygments == NULL || pyg_mod_formatters == NULL || pyg_mod_lexers == NULL || pyg_mod_styles == NULL) {
		logger("One of the modules could not be imported successfully.\n");
		return 0;
	}

	/** Success! **/
	return 1;
}

PyObject* get_function_from_module(PyObject* module, char* function_name) {
	return PyObject_GetAttrString(module, function_name);
}
