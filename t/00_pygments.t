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
	cmp_ok($formatted_code, 'eq', $expected_output, 'Simple hash successful');
}

{
	my $everything_went_allright = highlight({
		code => 'print "Hello World!";',
		lexer => 'perl',
		formatter => 'html',
		outfile => $ENV{PWD} . '/formatted_code.code'
	});
	cmp_ok($everything_went_allright, '==', 1, 'It should have written to the file correctly');

	# Let's check the contents of the file
	open(FH, '<', $ENV{PWD} . '/formatted_code.code');
	local $/ = undef;
	my $file_contents = <FH>;
	close(FH);

	my $expected_output = qq{<div class="highlight"><pre><span class="k">print</span> <span class="s">&quot;Hello World!&quot;</span><span class="p">;</span>\n</pre></div>\n};
	cmp_ok($file_contents, 'eq', $expected_output, 'Writing to formatted_code.code successful');
}

done_testing();
