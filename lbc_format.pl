open(FH, $ARGV[0]) or die "failed";

while(<FH>) {

	if($_ =~ /\(/) {
		@line = split /\(/, $_;
		$verses = pop @line;
		
		print "#$line[0] (";
		shift @line;
		
		foreach $i (@line) {
			print $i;
		}
	
		if($verses =~ /:/) {
			print "\n";
			@v = split /;/, $verses;
			foreach $x (@v) {
				print "$x\n";
			}
		} else {
			print "$verses (";
		}
	} else {
		print "#$_";
	}
	
}