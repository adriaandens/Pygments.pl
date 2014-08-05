HE* hashentry_from_hash(HV* hash, char* key);
SV* value_from_hashentry(HE* entry);
SV* key_from_hashentry(HE* entry);
PyObject* create_py_string_from_perl_string(SV* str)
