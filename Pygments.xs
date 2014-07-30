#include "EXCESS.h"

MODULE = Text::Pygments		PACKAGE = Text::Pygments

SV* highlight()
	CODE:
		RETVAL = newSVpvs("Ohayou!");
	OUTPUT: RETVAL
