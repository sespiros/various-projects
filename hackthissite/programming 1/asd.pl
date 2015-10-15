#!/usr/bin/perl
open WORDS, "words" or die $!;
open DIC, "dic" or die $!;
my @words = <WORDS>;
my @dic = <DIC>;
foreach $word (@words){
chomp($word);
$lenw=length($word);
foreach $list (@dic){
chomp($list);
$lenl=length($list);
if($list =~ m/^[$word]{$lenw}$/ && $word=~ m/^[$list]{$lenl}$/){
print "$list,";}}}
