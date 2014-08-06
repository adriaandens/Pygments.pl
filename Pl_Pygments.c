#include "Pl_Pygments.h"
#include "Py_Helper_ftns.h"
#include "Py_Pygments.h"

extern PyObject *pyg_mod_pygments, *pyg_mod_formatters, *pyg_mod_lexers, *pyg_mod_styles; /** Modules **/

PyObject* create_lexer(SV* lexer_options) {
	PyObject* lexer;
	if(SvTYPE(lexer_options) == SVt_PV) { /** We got a simple string **/
		PyObject* ftn_get_lexer_by_name = get_function_object(pyg_mod_lexers, "get_lexer_by_name");
		lexer = PyObject_CallFunction(ftn_get_lexer_by_name, "s", SvPV_nolen(lexer_options));
	} else { /** We got a hash **/
		PyObject* options = PyDict_New();
		char* lexer_type = SvPV_nolen(HeVAL(hv_fetch_ent(lexer_options, newSVpvs("type"), NULL, 0)));
		AV* keys = SvRV(get_list_of_keys(lexer_options));

		int i;
		for(i = 0; i < av_len(keys); i++) {
			SV** valptr = av_fetch(keys, i, 0); 
			char* key_name = SvPV_nolen(*valptr);
			if(strcmp(key_name, "type") != 0) {
				PyDict_SetItemString(options, key_name, SvREFCNT_inc(HeVAL(hv_fetch_ent(lexer_options, newSVpvs(key_name), NULL, 0))));
			}
		}

		/** Call function, get lexer by name with dict **/
		PyObject* args = Py_BuildValue("s", lexer_type);
		lexer = PyObject_Call(ftn_get_lexer_by_name, args, options);
	}
	return lexer;
}
PyObject* create_formatter(SV* formatter_options) {
	PyObject* formatter;
	if(SvTYPE(formatter_options) == SVt_PV) { /** We got a simple string **/
		PyObject* ftn_get_formatter_by_name = get_function_object(pyg_mod_formatters, "get_formatter_by_name");
		formatter = PyObject_CallFunction(ftn_get_formatter_by_name, "s", SvPV_nolen(formatter_options));
	} else { /** We got a hash **/
		PyObject* options = PyDict_New();
		char* formatter_type = SvPV_nolen(HeVAL(hv_fetch_ent(formatter_options, newSVpvs("type"), NULL, 0)));
		AV* keys = SvRV(get_list_of_keys(formatter_options));

		int i;
		for(i = 0; i < av_len(keys); i++) {
			SV** valptr = av_fetch(keys, i, 0); 
			char* key_name = SvPV_nolen(*valptr);
			if(strcmp(key_name, "type") != 0) {
				PyDict_SetItemString(options, key_name, SvREFCNT_inc(HeVAL(hv_fetch_ent(formatter_options, newSVpvs(key_name), NULL, 0))));
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

		return 0; /** One of those does not exist **/
	}


	/** Check code **/
	SV* code_value = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("code"), NULL, 0)));
	if(SvTYPE(code_value) != SVt_PV && 
	 !(SvTYPE(code_value) == SVt_RV && SvTYPE(SvRV(code_value)) == SVt_PV)) {
		return 0; /** Not a string or a reference to a string **/
	}	

	/** Check Lexer **/
	SV* lexer_value = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("lexer"), NULL, 0)));
	if(!SvPOK(lexer_value) && !(SvROK(lexer_value) && SvTYPE(lexer_value) == SVt_PVHV)) {
		return 0;
	}

	/** Check Formatter **/
	SV* formatter_value = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("formatter"), NULL, 0)));
	if(!SvPOK(formatter_value) && !(SvROK(formatter_value) && SvTYPE(formatter_value) == SVt_PVHV)) {
		return 0;
	}

	/** Check outfile **/
	if((int) hv_exists_ent(options, newSVpvs("outfile"), 0) == 0) {
		SV* outfile = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("outfile"), NULL, 0)));
		if(SvTYPE(outfile) != SVt_PV &&
		 !(SvTYPE(outfile) == SVt_RV && SvTYPE(SvRV(outfile)) == SVt_PV)) {
			    return 0;
		} else {
			return_code = 2;
		}
	}

	/** Everything OK! **/
	return return_code;
}
