package Text::Pygments;

use XSLoader;
use Exporter qw(import);

our $VERSION = '0.1';
our @EXPORT = qw(highlight); # Subroutines to export

XSLoader::load(__PACKAGE__, $VERSION);

1;
