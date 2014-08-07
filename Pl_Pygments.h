#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include<Python/Python.h>

PyObject* create_lexer(SV* lexer);
PyObject* create_formatter(SV* formatter);
int check_arguments(HV* options);
