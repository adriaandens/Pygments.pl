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
