#include "EXCESS.h"
#include "Pygments.h"
#include "Helper.h"
#include "Logger.h"

extern PyObject *pyg_mod_pygments, *pyg_mod_formatters, *pyg_mod_lexers, *pyg_mod_styles;

MODULE = Text::Pygments		PACKAGE = Text::Pygments

SV* highlight(HV* options)
	CODE:
		logger("Starting log...\n");

		int valid_arguments = check_arguments(options);
		if(valid_arguments < 0) {
			logger("Did not pass valid arguments checker.\n");
			XSRETURN_IV(-10);
		}

		logger("Passed the valid arguments checker.\n");

		int result = initialize_python_and_pygments_modules();
		if(result < 0) {
			logger("Failed to initialize Python and/or import the Pygments modules.\n");
			XSRETURN_IV(-1);
		}

		logger("Initialized Python and imported modules.\n");

		/** Create PyObjects for the parameters **/
		PyObject* code, * lexer, * formatter, * outfile;
		code = create_py_string_from_pl_string(value_from_hash(options, "code"));
		lexer = create_lexer(value_from_hash(options, "lexer"));
		formatter = create_formatter(value_from_hash(options, "formatter"));
		if(valid_arguments == 1)
			outfile = create_py_string_from_pl_string(value_from_hash(options, "outfile"));

		int error_number;
		if((error_number = error_occured(code, lexer, formatter))) {
			XSRETURN_IV(error_number);
		}

		/** Call highlight() in Python **/
		PyObject* pyg_ftn_highlight = PyObject_GetAttrString(pyg_mod_pygments, "highlight");
		PyObject* py_formatted_code = PyObject_CallFunctionObjArgs(pyg_ftn_highlight, code, lexer, formatter, NULL);
		if(valid_arguments == 1) {
			FILE* fp;
			fp = fopen(PyBytes_AsString(outfile), "w");
			
			/** Error checking **/
			if(fp == NULL)
				XSRETURN_IV(-50);

			fprintf(fp, "%s", PyBytes_AsString(py_formatted_code));
			fclose(fp);
			RETVAL = newSViv(1);
		} else {
			SV* pl_formatted_code = create_pl_string_from_py_string(py_formatted_code);
			RETVAL = pl_formatted_code;
		}	
	OUTPUT: RETVAL

