use strict;
use warnings;
use Test::More;

use Text::Pygments;

my $formatted_code = highlight({
	code => 'print "Hello World!";',
	lexer => 'perl',
	formatter => 'html'
});
print STDERR "\n---Formatted code----\n";
print STDERR $formatted_code;
print STDERR "\n\n";
ok(1, 'OK');

done_testing();
