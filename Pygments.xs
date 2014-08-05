#include "EXCESS.h"
#include "Pl_Helper_ftns.h"
#include "Pl_Pygments.h"
#include "Py_Pygments.h"


MODULE = Text::Pygments		PACKAGE = Text::Pygments

# Pygments API: pygments.highlight(code, lexer, formatter, outfile=None) 
SV* highlight(HV* options)
	CODE:
		int valid_arguments = check_arguments(options);
		if(!valid_arguments)
			XSRETURN_UNDEF;

		initialize_python_and_pygments_modules();

		/** Create PyObjects for the parameters **/
		PyObject* code = create_py_string_from_perl_string();
		PyObject* lexer = create_lexer();
		PyObject* formatter = create_formatter();
		PyObject* outfile = create_py_string_from_perl_string();

		/** Call highlight() in Python **/


		/** Convert PyObject to Perl String **/

		/** Return **/
		RETVAL = newSVpvs("Ohayou!");
	OUTPUT: RETVAL

