#Name: Cesar Cantu-Perez
#ID# 1001463763
#Perl 5.30.0
#Ubuntu VM

#!/usr/bin/perl

use strict;
use warnings;
use Cwd;
#The function directSize will return the size of a directory and its subdirectories
sub directSize
{
	#initializing 3 variables: directory will hold the directory that was passed in during the function call
	#sumSize will hold the total size of the directory
	#fileSize will hold the size of the current file that is being checked
	my $directory = $_[0];
	my $sumSize = $_[1];
	my $fileSize = 0;
	opendir(my $dir, $directory); 
	#while there are still items in the directory the fucntion will check to see whether the current filename is the
	#name of the directory or not. If the filename is for a directory it will be passed into the if statement and the
	#function will recursively call itself to find the size of the subdirectory
	while(my $filename = readdir($dir))
	{
		#skipping the . and .. directories
		if(($filename ne '.') && ($filename ne '..'))
		{
			#if filename is a directory call directSize again
			if(-d $filename)
			{
				$filename = $directory . "/" . $filename;
				$sumSize = directSize($filename, $sumSize);
			}
			#if filename is anything else use -s to find the size of the file and add the filesize to sumSize
			else
			{
				$filename = $directory . "/" . $filename;
				$fileSize = -s $filename;
				print("The filesize for $filename is: $fileSize bytes\n");
				$sumSize = $sumSize + $fileSize;
			}
		}
	}
	closedir($dir);
	return($sumSize);
	
}
#calling the directSize function to find the size of the directory 
my $size = 0;
my $currentdir = cwd();
$size = directSize($currentdir, $size);
print("The total size of the current directory is $size bytes.\n");