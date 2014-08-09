use strict;
use warnings;
use Test::More;

use Text::Pygments;

# HAPPY TESTS

# Test 1: code, lexer and formatter are valid strings
{
	my $formatted_code = highlight({
		code => 'print "Hello World!";',
		lexer => 'perl',
		formatter => 'html'
	});
	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok($formatted_code, 'eq', $expected_output, 'Simple hash successful');
}
# Test 2: code, lexer, formatter and outfile
{
	my $filename = 'code.pl';
	my $everything_went_allright = highlight({
		code => 'print "Hello World!";',
		lexer => 'perl',
		formatter => 'html',
		outfile => $filename
	});
	cmp_ok($everything_went_allright, '==', 1, 'Written to the file.');

	# Let's check the contents of the file
	open(FH, '<', $filename);
	local $/ = undef;
	my $file_contents = <FH>;
	close(FH);

	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok($file_contents, 'eq', $expected_output, qq{Contents of $filename looks good too!});
	unlink($filename);
}
# Test 3: Lexer has a hashref
{
	my $formatted_code = highlight({
		code => 'print "Hello World!";',
		lexer => {
			type => 'perl',
			stripnl => 'true',
			tabsize => 4,
			ensurenl => 'false',		
		},
		formatter => 'html'
	});
	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok($formatted_code, 'eq', $expected_output, 'Lexer as hashref returns expected code.');

}
# Test 4: Formatter has a hashref
{
	my $formatted_code = highlight({
		code => 'print "Hello World!";',
		lexer => 'perl',
		formatter => {
			type => 'html',
			title => 'Amazing Perl Code',
			full => 'true'
		}
	});
	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok($formatted_code, 'eq', $expected_output, 'Formatter as hashref returns expected code.');

}
# Test 5: Bogus key-value pairs apart from "type"
{
	my $hashref = {code => 'print "Hello World!";', lexer => {type => 'perl', one => 'two', two => 'three'}, formatter => {type => 'html', one => 'two', two => 'three'}};
	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok(highlight($hashref), 'eq', $expected_output, q{Bogus key-value pairs don't disturb the flow});
}
# Test 6: Code can be a stringref
{
	my $string = 'print "Hello World!";';
	my $hashref = {code => \$string, lexer => 'perl', formatter => 'html'};
	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok(highlight($hashref), 'eq', $expected_output, 'Code can be a stringref');
}
# Test 7: Outfile can be a stringref
{
	my $string = 'code.pl';
	my $hashref = {code => 'print "Hello World!";', lexer => 'perl', formatter => 'html', outfile => \$string};
	my $result = highlight($hashref);
	cmp_ok($result, '==', 1, 'Outfile can be a stringref');

	# Let's check the contents of the file
	open(FH, '<', $string);
	local $/ = undef;
	my $file_contents = <FH>;
	close(FH);

	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok($file_contents, 'eq', $expected_output, qq{Contents of $string looks good too!});
	unlink($string);
}

done_testing();
