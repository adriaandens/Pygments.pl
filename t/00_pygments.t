use strict;
use warnings;
use Test::More;

use Text::Pygments;

{
	my $formatted_code = highlight({
		code => 'print "Hello World!";',
		lexer => 'perl',
		formatter => 'html'
	});
	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok($formatted_code, 'eq', $expected_output, 'Simple hash successfull');
}

{
	my $formatted_code = highlight({
		code => 'print "Hello World!";',
		lexer => 'perl',
		formatter => 'html',
		outfile => 'formatted_code.code'
	});
	print STDERR "\n---Formatted code----\n";
	print STDERR $formatted_code;
	print STDERR "\n\n";

	#my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	#cmp_ok($formatted_code, 'eq', $expected_output, 'Simple hash successfull');

}

done_testing();
