use ExtUtils::MakeMaker;

WriteMakefile(
	NAME => 'Text::Pygments',
	VERSION_FROM => 'lib/Text/Pygments.pm',

	#LIBS           => ['-lPython'],
	DEFINE         => '',
	INC            => '-I.',
	OBJECT         => '$(O_FILES)',
);
