# Pygments.pl

This is a Perl wrapper around the well known Python syntax highlighter.

## Installation

Install Pygments and Install this module.

## Using this module

Basically you want to call highlight() with a big hash containing all your parameters. To fill in those parameters dynamically, you can use the modules Text::Pygments::Lexer, Text::Pygments::Formatter and Text::Pygments::Style.

Let's know look at the hash:
{
	code => 'print "Hello World!;',
	lexer => 'Perl',
	formatter => 'HTML',
	outfile => 'formatted_code.html'
}

{
	code => 'print "Hello World!;',
	lexer => {
		type => 'perl',
		stripnl => 1,
		tabsize => 4,
	},
	formatter => {
		type => 'html',
		html => {
			linenos => 1,
		},
		style => 'monokai',
		full => 0,
		title => 'Formatted Code',
	},
	outfile => 'formatted_code.html'
}
## Reference

### Text::Pygments

Subroutine highlight(): given a hash of settings, this subroutine returns formatted code.

### Text::Pygments::Lexer

Subroutine is_lexer(): returns true if the string provided is indeed a Lexer.
Subroutine get_lexer_for_filename(): returns a string with the name of the lexer that would be used.
Subroutine get_lexer_for_mimetype(): returns a string with the name of the lexer that would be used.
Subroutine guess_lexer(): returns a string with the name of the lexer that would be used.
Subroutine get_all_lexers(): returns a list of strings, containing all lexers.

### Text::Pygments::Formatter

Subroutine is_formatter(): returns true if the string provided is indeed a Formatter.
Subroutine get_formatter_for_filename(): returns a string with the name of the formatter that would be used.

### Text::Pygments::Style

Subroutine is_style(): returns true if the string provided is indeed a Style.
Subroutine get_all_styles(): returns a list of strings, containing all styles.
