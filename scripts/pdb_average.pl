#!/usr/bin/perl
#
# OMR, Bristol, 15 January 2020
# roscioni@gmail.com

$pdb ="%-6s%5i %-4s%1s%3s %1s%4i%1s   %8.3f%8.3f%8.3f%6.2f%6.2f          %-2s%2s\n";
$long="%-6s%5x %-4s%1s%3s %1s%4i%1s   %8.3f%8.3f%8.3f%6.2f%6.2f          %-2s%2s\n";

$help="Usage: pdb_average FILE.pdb\n
Read a PDB and average together the position of multiple atoms with
the same atom name in the same molecule.\n";

# Check the input arguments
for my $i(0 .. $#ARGV){
	if (-f $ARGV[$i]){$fileinput=$ARGV[$i];}
	elsif ($ARGV[$i] eq "-h"||$ARGV[$i] eq "--help"){die $help;}
}

# open pdb file for input
$mol=&first($fileinput);
open PDB, "<$fileinput";
# go through all lines in the PDB file
$count=0;
while (my $line=<PDB>)
{
    # record is one of these two
    if ($line =~ /^(ATOM|HETATM)/){
	
	# Parse the line.
	my @data=&parse_pdb($line);
	
	# Print the current molecule when the molecule change.
	if ($mol != $data[5]){
		$mol=$data[5];
		&moldump(\@current,\%coord,\%ref);
		undef @current;
		undef %coord;
		undef %ref;
	}
	
	# Store the data of the current molecule.
	push @current, \@data;
	$coord{$data[1]}[$_]+=$data[7+$_] for 0 .. 2;
	$ref{$data[1]}++;
	
    } elsif ($#current>0) {
    	# Print the last molecule.
	$mol=0;
	&moldump(\@current,\%coord,\%ref);
	undef @current;
	undef %coord;
	undef %ref;
	#print "current: $#current\n";
	print "$line";
    } else {
    	print "$line";
    }
    
}
close PDB;

# Print the last instance if the file does not contain a END line.
if ($#current>0) {
    	# Print the last molecule.
	$mol=0;
	&moldump(\@current,\%coord,\%ref);
	print "END\n";
}

sub clean {
        my $out=$_[0];
        # remove whitespaces.
        $out=~ s/[\s+\t+]//g;
        # remove marks (for the program align).
        $out =~ s/[+*\/]+//;
        return $out
}

# line format:  A6,I5,1X,A4,A1,A3,1X,A1,I4,A1,3X,3F8.3,2F6.2,10X,A2,A2
sub parse_pdb {
        my @out;
        chomp $_[0];
        $out[0]=substr($_[0],6,5);   # id
        $out[1]=substr($_[0],12,4);  # atm
        $out[2]=substr($_[0],16,1);  # alt
	$out[3]=substr($_[0],17,3);  # res
	$out[4]=substr($_[0],21,1);  # cid
	$out[5]=substr($_[0],22,4);  # seq
	$out[6]=substr($_[0],26,1);  # icd
        $out[7]=substr($_[0],30,8);  # x
        $out[8]=substr($_[0],38,8);  # y
        $out[9]=substr($_[0],46,8);  # z
        $out[10]=substr($_[0],54,6); # occupancy
	$out[11]=substr($_[0],60,6); # temp fact
	$out[12]=substr($_[0],76,2); # segid
	$out[13]=substr($_[0],78,2); # element
	for my $i (0 .. $#out){
		$out[$i]=clean($out[$i]);
	}
        return @out
}

sub pdb_line {
	# dereference the input array.                                                                                                                                                                                                                                                                                                                                          
	my $var=$_[0];
	@var=@$var;
	my $fmt=$pdb;
	$fmt=$long if $_[1] > 99999;
	printf $fmt,"ATOM",$_[1],$var[1],$var[2],$var[3],$var[4],$var[5],
	$var[6],$var[7],$var[8],$var[9],$var[10],$var[11],$var[12],$var[13];
}

# Find the id of the first molecule.
sub first {
	my $out=qx{sed '/^AT/q;/^HET/q' $_[0]|tail -1};
	my @data=&parse_pdb($out);
	return $data[5];
}

# Dump the current molecule.
sub moldump {
	# Keep the reference to the input arrays and hashs.                                                                                                                                                                                                                                                                                                                                          
	my @current=@{$_[0]};
	my %coord=%{$_[1]};
	my %ref=%{$_[2]};
	my %count;
	for my $i (0 .. $#current){
		$count{$current[$i][1]}++;
		
		# Average the position of the atom and print it.
		if ($count{$current[$i][1]}==$ref{$current[$i][1]}){
			$current[$i][7+$_]=$coord{$current[$i][1]}[$_]/$ref{$current[$i][1]} for 0 .. 2;
			# slice the AoA.
			my @atom;
			$atom[$_]=$current[$i][$_] for 0 .. 13;
			$count++;
			&pdb_line(\@atom,$count);
		}
	}
}
