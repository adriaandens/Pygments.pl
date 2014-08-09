use Test::More;
use Text::Pygments;

# CRASH TESTS

# Test 1: No Arguments
# Test 2: empty hashref
# Test 3: hashref with bogus key-value pairs
# Test 4: lexer contains a number
# Test 5: Repeat test 4 with formatter
# Test 6: Code is stringref
# Test 7: Code is not a string
# Test 8: Repeat test 6 and 7 with outfile
# Test 9: Lexer hash does not have "type" key
# Test 10: Repeat test 10 with formatter
# Test 11: Lexerstring is not a valid lexer
# Test 12: Repeat test 12 with formatter
# Test 13: Bogus key-value pairs apart from "type"

# HAPPY TESTS
# Test 1: code, lexer and formatter are valid strings
# Test 2: code, lexer, formatter and outfile
# Test 3: Lexer has a hashref
# Test 4: Formatter has a hashref




done_testing();
