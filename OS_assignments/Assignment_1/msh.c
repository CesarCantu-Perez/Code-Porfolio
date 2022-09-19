/*

  Name: Cesar Cantu-Perez
  ID:   1001463763

 */




// The MIT License (MIT)
//
// Copyright (c) 2016 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//This program creates your own shell environment similar to a terminal

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports four arguments

int main()
{

  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );
  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;

    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr;

    char *working_string  = strdup( command_string );

    // we are going to move the working_string pointer soexpected ')' before ' ' token
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *head_ptr = working_string;

    // Tokenize the input strings with whitespace used as the delimiter
    while ( ( (argument_ptr = strsep(&working_string, WHITESPACE ) ) != NULL) &&
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    char *arg[10];
	int pidCount, histCount, tokenCount = 0;  // TODO: turn token_count into a 2d array so I can save the token count of each command in history
	int token_index  = 0;
//This is where I started to implement my code

//history is a 2d array that will be used for the history and !n functions
//i and j are iterators for the for loops that I will be using
//pidHistory will hold the PIDS so I can call it in pidhistory
	char *history[14][10];
	int i, j = 0;
	int pidHistory[14];

//this for loop stores the tokens for the current command in arg[i] so we can use the tokens later
	for( token_index = 0; token_index < token_count; token_index ++ )
    {
       arg[token_index] = token[token_index];
    }
//this for loop takes the tokens that exist and stores them in history
//tokenCount is used for counting how many tokens were actually stored inside of a history[histCount]
	for( token_index = 0; token_index < token_count; token_index ++ )
    {
	   if(token[token_index] != NULL)
	   {
		   history[histCount][token_index] = token[token_index];
		   //printf("the token: %s\n", token[token_index]);
		   //printf("History will show: %s\n", history[histCount][token_index]);
		   tokenCount++;
	   }
    }
//histCount is iterated until it hits 15 then it becomes 0 so the history can continue to save history since it is limited to 14
	histCount++;

	if(histCount >=15)
	{
		histCount = 0;
	}
//this makes sure the when there is nothing entered as a command, it will print msh> on the next line
	if(arg[0] == NULL)
	{

	}
//this checks if the first argument is either quit or exit if it is it will return and exit the program
//since exit and quit are not part of the usr/bin commands, I had to implemented it manually
	else if((strcmp(arg[0], "quit") == 0 || (strcmp(arg[0], "exit")) == 0))
	{
		free(head_ptr);
		return 0;
	}
//this executes cd since it is not part of the usr/bin commands
//it uses chdir to change the current working directory of the program using the second argument
	else if((strcmp(arg[0], "cd")) == 0)
	{
		chdir(arg[1]);
	}
//this uses the pidHistory array that has the pids of the previous processes and prints them out
	else if((strcmp(arg[0], "pidhistory")) == 0)
	{
		for(i=0;i< pidCount;i++)
		{
			printf("%d: %d\n", i, pidHistory[i]);
		}
	}
//this shows the last 15 commands that were issued to the shell
//uses a double for loop to iterate through the 2d array
	else if((strcmp(arg[0], "history")) == 0)
	{
		for(i=0;i < histCount;i++)
		{
			printf("%d: ", i);
			for(j=0; j < token_count-1;j++)
			{
				if(history[i][j] != NULL)
				{
					printf("%s ", history[i][j]);
				}
			}
			printf("\n");
		}
	}
///////////////////////////////////////////////////////////////////////////
/////// The !n function takes the nth command and executes it again ///////
/////// it uses the 2d array history to execute the commands        ///////
///////////////////////////////////////////////////////////////////////////
	else if((strcmp(arg[0], "!0")) == 0)
	{
		if(history[0][0] != NULL)
		{
			printf("0: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[0][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!1")) == 0)
	{
		if(history[1][0] != NULL)
		{
			printf("1: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[1][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!2")) == 0)
	{
		if(history[2][0] != NULL)
		{
			printf("2: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[2][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!3")) == 0)
	{
		if(history[3][0] != NULL)
		{
			printf("3: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[3][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!4")) == 0)
	{
		if(history[4][0] != NULL)
		{
			printf("4: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[4][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!5")) == 0)
	{
		if(history[5][0] != NULL)
		{
			printf("5: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[5][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!6")) == 0)
	{
		if(history[6][0] != NULL)
		{
			printf("6: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[6][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!7")) == 0)
	{
		if(history[7][0] != NULL)
		{
			printf("7: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[7][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!8")) == 0)
	{
		if(history[8][0] != NULL)
		{
			printf("8: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[8][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!9")) == 0)
	{
		if(history[9][0] != NULL)
		{
			printf("9: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[9][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!10")) == 0)
	{
		if(history[10][0] != NULL)
		{
			printf("10: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[10][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!11")) == 0)
	{
		if(history[11][0] != NULL)
		{
			printf("11: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[11][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!12")) == 0)
	{
		if(history[12][0] != NULL)
		{
			printf("12: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[12][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!13")) == 0)
	{
		if(history[13][0] != NULL)
		{
			printf("13: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[13][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
	else if((strcmp(arg[0], "!14")) == 0)
	{
		if(history[14][0] != NULL)
		{
			printf("14: ");
			for(i=0; i < token_count-1;i++)
			{
				printf("%s ", history[14][i]);
			}
			printf("\n");
		}
		else
		{
			printf("Command not in history.\n");
		}
	}
///////////////////////////////////////////////////////////////////////////
/////// The end of the !n functions ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// this forks a new process to execute the execvp function by passing in the commands that are saved at arg[] array
	else
	{
		tokenCount = 0;
		pid_t pid = fork();
		if(pid == 0)
		{
			int ret = execvp(arg[0], &arg[0]);
			if(ret == -1)
			{
				printf("%s: command not found\n", arg[0]);
			}
		}
		else
		{
			int status;
			wait(&status);
			pidHistory[pidCount] = pid;
			pidCount++;
			if(pidCount >= 15)
			{
				pidCount = 0;
			}
		}
	}
	tokenCount = 0;

    free( head_ptr );

  }
  return 0;
  // e2520ca2-76f3-11ec-90d6-0242ac120003
}
