package Text::Pygments::Lexer;

use XSLoader;
use Exporter qw(import);

our $VERSION = '0.1';
our @EXPORT = qw(is_lexer get_lexer_for_filename get_lexer_for_mimetype guess_lexer get_all_lexers);

XSLoader::load(__PACKAGE__, $VERSION);

1;
