use strict;
use warnings;
use Test::More;

use Text::Pygments;

cmp_ok(highlight(), 'eq', 'Ohayou!', qq(Prints "Ohayou!"));


done_testing();
