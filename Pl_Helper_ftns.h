#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include<Python/Python.h>

PyObject* create_py_string_from_pl_string(SV* str);
SV* value_from_hash(HV* hash, char* key);
AV* get_list_of_keys(HV* hash);
