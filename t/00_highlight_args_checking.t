use strict;
use warnings;
use Test::More;

use Text::Pygments;

# CRASH TESTS

# Test 1: No Arguments
ok(!defined(highlight()), 'No arguments returns undef');
# Test 2: empty hashref
ok(!defined(highlight({})), 'Empty hashref returns undef');
# Test 3: hashref with bogus key-value pairs
{
	my $hashref = {one => 'two', two => 'three', three => 'four'};
	ok(!defined(highlight($hashref)), 'Not having code, lexer and formatter as keys, returns undef');
}
# Test 4: lexer contains a number
{
	my $hashref = {code => 'print "Hello World!";', lexer => 42, formatter => 'html'};
	ok(!defined(highlight($hashref)), 'Lexer has invalid Scalar type, returns undef');
}
# Test 5: Repeat test 4 with formatter
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 31337};
	ok(!defined(highlight($hashref)), 'Formatter has invalid Scalar type, returns undef');
}
# Test 6: Code is stringref
{
	my $string = 'print "Hello World!";';
	my $hashref = {code => \$string, lexer => 'perl', formatter => 'html'};
	ok(!defined(highlight($hashref)), 'Code cannot be a string ref (for now), returns undef');
}
# Test 7: Code is not a string
{
	my $hashref = {code => 0xdeadbeef, lexer => 'perl', formatter => 'html'};
	ok(!defined(highlight($hashref)), 'Code cannot be a number, returns undef');
}
# Test 8: Repeat test 6 and 7 with outfile
{
	my $string = 'code.pl';
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'html', outfile => \$string};
	ok(!defined(highlight($hashref)), 'Outfile cannot be a string ref (for now), returns undef');

	$hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'html', outfile => 0xcafec0de};
	ok(!defined(highlight($hashref)), 'Outfile cannot be a number, returns undef');
}
# Test 9: Lexer hash does not have "type" key
{
	my $hashref = {code => 'print "Hello World!";', lexer => {one => 'two', two => 'three', three => 'four'}, formatter => 'html'};
	ok(!defined(highlight($hashref)), 'Lexer without typekey, returns undef');
}
# Test 10: Repeat test 9 with formatter
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => {one => 'two', two => 'three', three => 'four'}};
	ok(!defined(highlight($hashref)), 'Formatter without typekey, returns undef');
}
# Test 11: Lexerstring is not a valid lexer
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'not a valid lexer', formatter => 'html'};
	ok(!defined(highlight($hashref)), 'Lexer is not a valid lexer, returns undef');
}
# Test 12: Repeat test 11 with formatter
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'not a valid formatter'};
	ok(!defined(highlight($hashref)), 'Formatter is not a valid formatter, returns undef');
}
# Test 13: Cannot write outfile to destination
{
	my $file = '/woopsie/daisy/code.pl';
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'html', outfile => $file};
	ok(!defined(highlight($hashref)), 'Cannot write to file, returns undef');
	unlink($file) if -e $file; # In case it succeeded, WOOPS!
}

done_testing();
