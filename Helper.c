#include "Helper.h"
#include "Logger.h"

SV* create_pl_string_from_py_string(PyObject* py_string) {
	char* str = PyBytes_AsString(py_string);
	return SvREFCNT_inc(newSVpvn(str, strlen(str)));
}

PyObject* get_function_object(PyObject* module, char* function_name) {
	return PyObject_GetAttrString(module, function_name);
}

PyObject* create_py_string_from_pl_string(SV* str) {
	logger("Perl string -> Py String: ");
	logger(SvPV_nolen(str)); logger("\n");
	return Py_BuildValue("s", SvPV_nolen(str));
}

SV* value_from_hash(HV* hash, char* key) {
	return SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvn(key, strlen(key)), NULL, 0)));
}

AV* get_list_of_keys(HV* hash) {
	AV* keys = newAV();
	SV* sv; char* key; I32 klen; /** Used in the loop **/
	hv_iterinit(hash);
	while((sv = hv_iternextsv(hash, &key, &klen)))
		av_push(keys, newSVpv(key, klen));

	return keys;
}

PyObject* get_function_from_module(PyObject* module, char* function_name) {
	return PyObject_GetAttrString(module, function_name);
}

PyObject* create_py_tuple(int number_of_args, ...) {
	va_list ap;
	PyObject* tuple = PyTuple_New(number_of_args);

	/** Iterate through list and add to tuple **/
	va_start(ap, number_of_args);
	int i;
	for(i = 0; i < number_of_args; i++) {
		PyTuple_SetItem(tuple, i, va_arg(ap, PyObject*));
	}
	va_end(ap);

	return tuple;
}

PyObject* create_py_dict(int number_of_pairs, ...) {
	PyObject* dict = PyDict_New();
	va_list ag;
	int i;

	va_start(ag, number_of_pairs);
	for(i = 0; i < number_of_pairs*2; i = i+2) {
		PyObject* key = va_arg(ag, PyObject*);
		PyObject* val = va_arg(ag, PyObject*);
		if(strcmp("true", PyBytes_AsString(val)) == 0)
			val = Py_True;
		else if(strcmp("false", PyBytes_AsString(val)) == 0)
			val = Py_False;
		else if(strcmp("none", PyBytes_AsString(val)) == 0)
			val = Py_None;

		PyDict_SetItem(dict, key, val);
	}
	va_end(ag);

	return dict;
}
