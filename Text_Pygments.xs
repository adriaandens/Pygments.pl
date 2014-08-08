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
		if(!valid_arguments) {
			logger("Did not pass valid arguments checker.\n");
			XSRETURN_UNDEF;
		}

		logger("Passed the valid arguments checker.\n");

		int result = initialize_python_and_pygments_modules();
		if(result == 0) {
			logger("Failed to initialize Python and/or import the Pygments modules.\n");
			XSRETURN_UNDEF;
		}

		logger("Initialized Python and imported modules.\n");

		/** Create PyObjects for the parameters **/
		PyObject* code, * lexer, * formatter, * outfile;
		code = create_py_string_from_pl_string(value_from_hash(options, "code"));
		lexer = create_lexer(value_from_hash(options, "lexer"));
		formatter = create_formatter(value_from_hash(options, "formatter"));
		if(valid_arguments == 2)
			outfile = create_py_string_from_pl_string(value_from_hash(options, "outfile"));

		/** Call highlight() in Python **/
		PyObject* pyg_ftn_highlight = PyObject_GetAttrString(pyg_mod_pygments, "highlight");
		PyObject* py_formatted_code;
		if(valid_arguments == 2)
			py_formatted_code = PyObject_CallFunctionObjArgs(pyg_ftn_highlight, code, lexer, formatter, outfile, NULL);
		else
			py_formatted_code = PyObject_CallFunctionObjArgs(pyg_ftn_highlight, code, lexer, formatter, NULL);
			

		/** Convert PyObject to Perl String **/
		SV* pl_formatted_code = create_pl_string_from_py_string(py_formatted_code);

		/** Return **/
		RETVAL = pl_formatted_code;
	OUTPUT: RETVAL

