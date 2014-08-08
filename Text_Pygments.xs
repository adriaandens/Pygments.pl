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
			outfile = create_py_filehandle(SvPV_nolen(value_from_hash(options, "outfile")), "w");

		/** Call highlight() in Python **/
		PyObject* pyg_ftn_highlight = PyObject_GetAttrString(pyg_mod_pygments, "highlight");
		PyObject* py_formatted_code;
		if(valid_arguments == 2) {
			PyObject* args = create_py_tuple(3, code, lexer, formatter);
			PyObject* dict = create_py_dict(1, "outfile", outfile);
			if(args == NULL)
				logger("Args is NULL.\n");
			if(dict == NULL)
				logger("Dict is NULL.\n");
			logger("Created tuple and dictionary for the call.\n");
			PyFile_IncUseCount(outfile);
			PyObject_Call(pyg_ftn_highlight, args, dict);
			PyFile_DecUseCount(outfile);
			RETVAL = newSViv(1);
		} else {
			py_formatted_code = PyObject_CallFunctionObjArgs(pyg_ftn_highlight, code, lexer, formatter, NULL);
			SV* pl_formatted_code = create_pl_string_from_py_string(py_formatted_code);
			RETVAL = pl_formatted_code;
		}	
	OUTPUT: RETVAL

