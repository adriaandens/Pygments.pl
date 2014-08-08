#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include<Python/Python.h>

#include "Helper.h" 

int initialize_python_and_pygments_modules();
PyObject* create_lexer(SV* lexer);
PyObject* create_formatter(SV* formatter);
int check_arguments(HV* options);
