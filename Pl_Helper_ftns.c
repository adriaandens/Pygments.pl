#include "Pl_Helper_ftns.h"

HE* hashentry_from_hash(HV* hash, char* key);
SV* value_from_hashentry(HE* entry);
SV* key_from_hashentry(HE* entry);

PyObject* create_py_string_from_pl_string(SV* str) {
	return Py_BuildValue("s", SvPV_nolen(str));
}

SV* value_from_hash(HV* hash, char* key) {
	return SvREFCNT(HeVAL(hv_fetch_ent(hash, key, NULL, 0)));
}
