#include "Pygments.h"
#include "Logger.h"

PyObject *pyg_mod_pygments, *pyg_mod_formatters, *pyg_mod_lexers, *pyg_mod_styles; /** Modules **/

int initialize_python_and_pygments_modules() {
	if(Py_IsInitialized()) {
		return 0;
	}

	Py_Initialize();
	pyg_mod_pygments = PyImport_ImportModule("pygments");
	pyg_mod_formatters = PyImport_ImportModule("pygments.formatters");
	pyg_mod_lexers = PyImport_ImportModule("pygments.lexers");
	pyg_mod_styles = PyImport_ImportModule("pygments.styles");
	if(pyg_mod_pygments == NULL || pyg_mod_formatters == NULL || pyg_mod_lexers == NULL || pyg_mod_styles == NULL) {
		return -1;
	}

	/** Success! **/
	return 0;
}

PyObject* create_lexer(SV* lexer_options) {
	PyObject* lexer;
	PyObject* ftn_get_lexer_by_name = get_function_object(pyg_mod_lexers, "get_lexer_by_name");
	if(SvTYPE(lexer_options) == SVt_PV) { /** We got a simple string **/
		lexer = PyObject_CallFunction(ftn_get_lexer_by_name, "s", SvPV_nolen(lexer_options));
	} else { /** We got a hash **/
		PyObject* options = PyDict_New();
		HV* lexer_options_hash = (HV*) SvRV(lexer_options);
		char* lexer_type = SvPV_nolen(value_from_hash(lexer_options_hash, "type"));
		AV* keys = get_list_of_keys(lexer_options_hash);

		int i;
		for(i = 0; i < av_len(keys); i++) {
			SV** valptr = av_fetch(keys, i, 0); 
			char* key_name = SvPV_nolen(*valptr);
			if(strcmp(key_name, "type") != 0) {
				PyDict_SetItemString(options, key_name, create_pyobject_from_sv(value_from_hash(lexer_options_hash, key_name)));
			}
		}

		/** Call function, get lexer by name with dict **/
		PyObject* args = create_py_tuple(1, Py_BuildValue("s", lexer_type));
		lexer = PyObject_Call(ftn_get_lexer_by_name, args, options);
	}
	if(PyErr_Occurred()) {
		PyErr_Clear(); /** We don't care, lexer will be NULL anyway **/
	}

	return lexer;
}

PyObject* create_formatter(SV* formatter_options) {
	PyObject* formatter;
	PyObject* ftn_get_formatter_by_name = get_function_object(pyg_mod_formatters, "get_formatter_by_name");
	if(SvTYPE(formatter_options) == SVt_PV) { /** We got a simple string **/
		formatter = PyObject_CallFunction(ftn_get_formatter_by_name, "s", SvPV_nolen(formatter_options));
	} else { /** We got a hash **/
		PyObject* options = PyDict_New();
		HV* formatter_options_hash = (HV*) SvRV(formatter_options);
		char* formatter_type = SvPV_nolen(value_from_hash(formatter_options_hash, "type"));
		AV* keys = get_list_of_keys(formatter_options_hash);

		int i;
		for(i = 0; i < av_len(keys); i++) {
			SV** valptr = av_fetch(keys, i, 0); 
			char* key_name = SvPV_nolen(*valptr);
			if(strcmp(key_name, "type") != 0) {
				PyDict_SetItemString(options, key_name, create_pyobject_from_sv(value_from_hash(formatter_options_hash, key_name)));
			}
		}

		/** Call function, get lexer by name with dict **/
		PyObject* args = create_py_tuple(1, Py_BuildValue("s", formatter_type));
		formatter = PyObject_Call(ftn_get_formatter_by_name, args, options);
	}
	if(PyErr_Occurred()) {
		PyErr_Clear(); /** We don't care, formatter will be NULL anyway **/
	}

	return formatter;
}

/** Return a negative value (see docs) on fail, and 0 or more (see docs) on success. **/
int check_arguments(HV* options) {
	int return_code = 0;

	/** Check if code, lexer and formatter keys exists **/
	if((int) hv_exists_ent(options, newSVpvs("code"), 0) == 0 ||
	   (int) hv_exists_ent(options, newSVpvs("lexer"), 0) == 0 ||
	   (int) hv_exists_ent(options, newSVpvs("formatter"), 0) == 0) {
		return -1; /** One of those does not exist **/
	}


	/** Check code **/
	SV* code_value = value_from_hash(options, "code");
	if(!SvPOK(code_value) && !(SvROK(code_value) && SvTYPE(SvRV(code_value)) == SVt_PV)) {
		return -1; /** Not a string or a reference to a string **/
	}	

	/** Check Lexer **/
	SV* lexer_value = value_from_hash(options, "lexer");
	if(!SvPOK(lexer_value) && !(SvROK(lexer_value) && SvTYPE(SvRV(lexer_value)) == SVt_PVHV)) {
		return -1;
	} else if(SvROK(lexer_value) && SvTYPE(SvRV(lexer_value)) == SVt_PVHV) {
		if(check_existence_of_hash_keys((HV*) SvRV(lexer_value), 1, "type") == 0)
			return -1;
	}

	/** Check Formatter **/
	SV* formatter_value = value_from_hash(options, "formatter");
	if(!SvPOK(formatter_value) && !(SvROK(formatter_value) && SvTYPE(SvRV(formatter_value)) == SVt_PVHV)) {
		return -1;
	} else if(SvROK(formatter_value) && SvTYPE(SvRV(formatter_value)) == SVt_PVHV) {
		if(check_existence_of_hash_keys((HV*) SvRV(formatter_value), 1, "type") == 0)
			return -1;
	}

	/** Check outfile **/
	if((int) hv_exists_ent(options, newSVpvs("outfile"), 0) != 0) {
		SV* outfile = value_from_hash(options, "outfile");
		if(!SvPOK(outfile) && !(SvROK(outfile) && SvTYPE(SvRV(outfile)) == SVt_PV)) {
			return -1;
		} else {
			return_code = 1;
		}
	}

	/** Everything OK! **/
	return return_code;
}

int error_occured(PyObject* code, PyObject* lexer, PyObject* formatter) {
	int error = 0; /** No error **/

	if(code == NULL)
		error = -20;
	else if(lexer == NULL) 
		error = -30;
	else if(formatter == NULL)
		error = -40;

	return error;
}
