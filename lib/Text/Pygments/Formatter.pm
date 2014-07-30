package Text::Pygments::Formatter;

use XSLoader;
use Exporter qw(import);

our $VERSION = '0.1';
our @EXPORT = qw(is_formatter get_formatter_for_filename);

XSLoader::load(__PACKAGE__, $VERSION);

1;
