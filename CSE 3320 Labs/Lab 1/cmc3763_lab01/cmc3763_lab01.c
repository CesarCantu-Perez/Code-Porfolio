//Name: Cesar Cantu-Perez
//UTA ID: 1001463763
//Lang ver: GCC 8.1.0
//OS: Windows 10



/*1. It was easier and faster for me to write the code for this lab using python. Python programs are typically shorter than other programs written in a language like c. Also using directory functions were way easier for me to understand and implement in python.

  2. To simulate recursion you could use a while loop that would break once it reaches the end of what it is supposed to be doing. A downside to that approach would be that you would have to set a limit to what the result could be (i.e. a maximum number of loops).*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

//function to calculate file size
int direct_size(char *directory, int sum);

int direct_size(char *directory, int sum)
{
    DIR *newDirect = opendir(directory);
	char nextDir[100];
	char fileName[100];
    struct dirent *entry;
    struct stat check;
	int comp, comp2, filesize = 1;
    //will check to see if directory has successfully been opened
    if(newDirect == NULL)
    {
        printf("Unable to access directory.");
    }
    else
    {
        //option to read all names from directory
        //printf("Directory opened!\n");
		//will read through directory adding up the size of files until it reaches a directory where it will call direct_size again
        while((entry = readdir(newDirect)) != NULL)
        {
            // get rid of the . and .. directories
			comp = strcmp(entry->d_name, ".");
            comp2 = strcmp(entry->d_name,"..");
			if(comp == 0 || comp2 == 0)
			{
				
			}
			else
			{
				//check to see if it is a directory or a file
				strcpy(fileName, directory);
				strcat(fileName, "/");
				strcat(fileName, entry->d_name);
				stat(fileName, &check);
				if(entry->d_type == DT_DIR)
				{
					//adds to the path name so direct_size can open the next directory
					printf("Directory: %s\n", entry->d_name);
					//strcpy(nextDir, directory);
					//strcat(nextDir, "/");
					//strcat(nextDir, entry->d_name);
					//printf("sum to be passed in: %d\n", sum);
					sum = direct_size(fileName, sum);
				}
				else
				{
					//adds the size to the sum of bytes already calculated
					printf("%s ", fileName);
					filesize = check.st_size;
					//printf("%d + ", sum);
					sum = sum + check.st_size;
					printf("%d bytes\n", sum);
					
				}
			}
        }
    }
	return sum;
}

int main()
{
    char direct;
	direct = '.';
	int sum = 0;
    //uses the direct as a path for the direct_size
    sum = direct_size(&direct, sum);
	printf("The size of the directory and its subdirectories is %d bytes.\n", sum);
    return 0;
}
