#include "Py_Pygments.h"
#include "Pl_Pygments.h"
#include "Pl_Helper_ftns.h"
#include "Py_Helper_ftns.h"
#include "Logger.h"

/**extern PyObject *pyg_mod_pygments, *pyg_mod_formatters, *pyg_mod_lexers, *pyg_mod_styles;**/

PyObject* create_lexer(SV* lexer_options) {
	logger("create_lexer() says hai!\n");
	PyObject* lexer;
	if(pyg_mod_lexers == NULL)
		logger("create_lexer(): pyg_mod_lexers is NULL.\n");
	PyObject* ftn_get_lexer_by_name = get_function_object(pyg_mod_lexers, "get_lexer_by_name");
	if(SvTYPE(lexer_options) == SVt_PV) { /** We got a simple string **/
		logger("create_lexer(): The lexer is a string.\n");
		lexer = PyObject_CallFunction(ftn_get_lexer_by_name, "s", SvPV_nolen(lexer_options));
	} else { /** We got a hash **/
		logger("create_lexer(): The lexer is a hash reference.\n");
		HV* lexer_options_hash = (HV*) SvRV(lexer_options);
		PyObject* options = PyDict_New();
		char* lexer_type = SvPV_nolen(HeVAL(hv_fetch_ent(lexer_options_hash, newSVpvs("type"), NULL, 0)));
		AV* keys = get_list_of_keys(lexer_options_hash);

		logger("Keys of hash: ");
		int i;
		for(i = 0; i < av_len(keys); i++) {
			SV** valptr = av_fetch(keys, i, 0); 
			char* key_name = SvPV_nolen(*valptr);
			logger(key_name);logger(" - ");
			if(strcmp(key_name, "type") != 0) {
				PyDict_SetItemString(options, key_name, create_py_string_from_pl_string(value_from_hash(lexer_options_hash, key_name)));
			}
		}
		logger("\n");

		/** Call function, get lexer by name with dict **/
		PyObject* args = Py_BuildValue("s", lexer_type);
		lexer = PyObject_Call(ftn_get_lexer_by_name, args, options);
	}
	if(lexer)
		logger("create_lexer(): It created 'a' Python object.\n");
	else
		logger("create_lexer(): Aw man, lexer is NULL.\n");
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
		char* formatter_type = SvPV_nolen(HeVAL(hv_fetch_ent(formatter_options_hash, newSVpvs("type"), NULL, 0)));
		AV* keys = get_list_of_keys(formatter_options_hash);

		int i;
		for(i = 0; i < av_len(keys); i++) {
			SV** valptr = av_fetch(keys, i, 0); 
			char* key_name = SvPV_nolen(*valptr);
			if(strcmp(key_name, "type") != 0) {
				PyDict_SetItemString(options, key_name, create_py_string_from_pl_string(value_from_hash(formatter_options_hash, key_name)));
			}
		}

		/** Call function, get lexer by name with dict **/
		PyObject* args = Py_BuildValue("s", formatter_type);
		formatter = PyObject_Call(ftn_get_formatter_by_name, args, options);
	}
	return formatter;
}

/** Return zero if it's not a good hash, return 1 if it is and there is no outfile, return 2 if it's also a valid hash and there's an outfile **/
int check_arguments(HV* options) {
	int return_code = 1;

	/** Check if code, lexer and formatter keys exists **/
	if((int) hv_exists_ent(options, newSVpvs("code"), 0) == 0 ||
	   (int) hv_exists_ent(options, newSVpvs("lexer"), 0) == 0 ||
	   (int) hv_exists_ent(options, newSVpvs("formatter"), 0) == 0) {
		logger("A key (code, lexer or formatter) was not found in the hash.\n");
		return 0; /** One of those does not exist **/
	}


	/** Check code **/
	SV* code_value = value_from_hash(options, "code");
	if(SvTYPE(code_value) != SVt_PV && 
	 !(SvTYPE(code_value) == SVt_RV && SvTYPE(SvRV(code_value)) == SVt_PV)) {
		logger("Code is neither a string, nor a reference to a string.\n");
		return 0; /** Not a string or a reference to a string **/
	}	

	/** Check Lexer **/
	SV* lexer_value = value_from_hash(options, "lexer");
	if(!SvPOK(lexer_value) && !(SvROK(lexer_value) && SvTYPE(lexer_value) == SVt_PVHV)) {
		logger("Lexer is neither a string nor a reference to a hash.\n");
		return 0;
	}

	/** Check Formatter **/
	SV* formatter_value = value_from_hash(options, "lexer");
	if(!SvPOK(formatter_value) && !(SvROK(formatter_value) && SvTYPE(formatter_value) == SVt_PVHV)) {
		logger("Formatter is neither a string nor a reference to a hash.\n");
		return 0;
	}

	/** Check outfile **/
	if((int) hv_exists_ent(options, newSVpvs("outfile"), 0) != 0) {
		logger("There is a key called outfile.\n");
		SV* outfile = value_from_hash(options, "outfile");
		if(SvTYPE(outfile) != SVt_PV &&
		 !(SvTYPE(outfile) == SVt_RV && SvTYPE(SvRV(outfile)) == SVt_PV)) {
				logger("But the key is not a valid one...\n");
			    return 0;
		} else {
			logger("The value of outfile is a string or a reference to one.\n");
			return_code = 2;
		}
	}
	logger("Everything seems ok in check_arguments().\n");

	/** Everything OK! **/
	return return_code;
}
