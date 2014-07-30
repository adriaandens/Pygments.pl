package Text::Pygments::Style;

use XSLoader;
use Exporter qw(import);

our $VERSION = '0.1';
our @EXPORT = qw(is_style get_all_styles);

XSLoader::load(__PACKAGE__, $VERSION);

1;
