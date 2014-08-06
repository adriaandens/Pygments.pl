#include "Pl_Pygments.h"

PyObject* create_lexer(HV* lexer) {}
PyObject* create_formatter(HV* formatter) {}

/** Return zero if it's not a good hash, return 1 if it is **/
int check_arguments(HV* options) {
	/** Check if code, lexer and formatter keys exists **/
	if((int) hv_exists_ent(options, newSVpvs("code"), 0) == 0 ||
	   (int) hv_exists_ent(options, newSVpvs("lexer"), 0) == 0 ||
	   (int) hv_exists_ent(options, newSVpvs("formatter"), 0) == 0) {

		return 0; /** One of those does not exist **/
	}


	/** Check code **/
	SV* code_value = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("code"), NULL, 0)));
	if(SvTYPE(code_value) != SVt_PV && 
	 !(SvTYPE(code_value) == SVt_RV && SvTYPE(SvRV(code_value)) == SVt_PV)) {
		return 0; /** Not a string or a reference to a string **/
	}	

	/** Check Lexer **/
	SV* lexer_value = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("lexer"), NULL, 0)));
	if(!SvPOK(lexer_value) && !(SvROK(lexer_value) && SvTYPE(lexer_value) == SVt_PVHV)) {
		return 0;
	}

	/** Check Formatter **/
	SV* formatter_value = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("formatter"), NULL, 0)));
	if(!SvPOK(formatter_value) && !(SvROK(formatter_value) && SvTYPE(formatter_value) == SVt_PVHV)) {
		return 0;
	}

	/** Check outfile **/
	if((int) hv_exists_ent(options, newSVpvs("outfile"), 0) == 0) {
		SV* outfile = SvREFCNT_inc(HeVAL(hv_fetch_ent(hash, newSVpvs("outfile"), NULL, 0)));
		if(SvTYPE(outfile) != SVt_PV &&
		 !(SvTYPE(outfile) == SVt_RV && SvTYPE(SvRV(outfile)) == SVt_PV)) {
			    return 0;
		}
	}

	/** Everything OK! **/
	return 1;
}
