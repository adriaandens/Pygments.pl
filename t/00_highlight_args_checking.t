use strict;
use warnings;
use Test::More;

use Text::Pygments;

# CRASH TESTS

# Test 1: No Arguments
{
	eval {my $result = highlight()};
	ok($@, q{Give error when calling highlight without an argument});
}
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
# Test 6: Code is not a string
{
	my $hashref = {code => 42, lexer => 'perl', formatter => 'html'};
	ok(!defined(highlight($hashref)), 'Code cannot be a number, returns undef');
}
# Test 7: Repeat test 6 with outfile
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'html', outfile => 0xcafec0de};
	ok(!defined(highlight($hashref)), 'Outfile cannot be a number, returns undef');
}
# Test 8: Lexer hash does not have "type" key
{
	my $hashref = {code => 'print "Hello World!";', lexer => {one => 'two', two => 'three', three => 'four'}, formatter => 'html'};
	ok(!defined(highlight($hashref)), 'Lexer without typekey, returns undef');
}
# Test 9: Repeat test 8 with formatter
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => {one => 'two', two => 'three', three => 'four'}};
	ok(!defined(highlight($hashref)), 'Formatter without typekey, returns undef');
}
# Test 10: Lexerstring is not a valid lexer
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'not a valid lexer', formatter => 'html'};
	my $return_value = highlight($hashref);
	ok($return_value <= -30 && $return_value > -40, 'Lexer is not a valid lexer, returns errorvalue between [-30,-40[');
}
# Test 11: Repeat test 11 with formatter
{
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'not a valid formatter'};
	my $return_value = highlight($hashref);
	ok($return_value <= -40 && $return_value > -50, 'Formatter is not a valid formatter, returns errorvalue between [-40,-50[');
}
# Test 12: Cannot write outfile to destination
{
	my $file = '/woopsie/daisy/code.pl';
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'html', outfile => $file};
	my $return_value = highlight($hashref);
	ok($return_value <= -50 && $return_value > -60, 'Cannot write to file, returns errorvalue between [-50, -60[');
	unlink($file) if -e $file; # In case it succeeded, WOOPS!
}

done_testing();
