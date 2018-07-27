#!/usr/bin/perl
use strict;
use warnings;
system ( "rm a.out" );
system ( "g++ -std=c++11 $ARGV[0]" );
my $i = 1;
while ( $i < @ARGV ) {
    print ( '-' x 70 . "\n" );
    print ( "\t\t\t\tTEST $i \n" );
    system ( "./a.out < $ARGV[$i]" );
    $i ++;
}

# usage example : 
#
#$ ./r b.cpp in1 in2 in3
#
