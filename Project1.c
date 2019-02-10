/*************************************************************************************
File Name: Project1.c

Objective: Create child proccesses while keeping track of their process ID and the
order they were created.  Also, depending on the input, have the processes simply end
or execute a different program.

Created By: Kristopher Lowell
Date Created: 2/9/2019

File History:
	Created - Approx. 3 hours - KCL - 2/9/2019
*************************************************************************************/

#include <stdio.h>																	// Needed for printf and related functions
#include <stdlib.h>																	// Needed for atoi function
#include <unistd.h>																	// Needed for fork function, and other process related functions
#include <sys/types.h>																// Needed for pid_t type (on some compilers)
#include <sys/wait.h>																// Needed for wait function

int main(int argc, char* argv[])
{
	pid_t pid = getpid();															// Process ID holding variable
	int child, limit;																// Index and end of for loops
	char s[] = "./testx";															// String that will hold which executable to commit to a child process

	printf("Parent pid is %d\n", pid);

	if(argc == 1)																	// If no argument is passed for number of children to create
	{
		for(child = 0; child < 10; child++)											// Then default is to create 10 children that simply terminate
		{
			pid = fork();															// Create a child process with the same text, at the same point
			if(pid < 0)
			{
				fprintf(stderr, "Fork failed.\n");									// In case of an error, exit the process
				exit(1);
			}
			else if (pid == 0)
			{
				pid = getpid();														// When in a child process, print that it just started, and then
				printf("Started child %d with pid %d\n", child + 1, pid);			// avoid making children of children by avoiding the for loop
				child = 10;
				pid = 0;
			}
		}

		if(pid > 0)																	// Don't want child processes waiting on children that don't exist
		{
			for (child = 0; child < 10; child++)									// Wait for all 10 children to finish before parent continues to
			{																		// orphaning children
				pid = wait(NULL);
				printf("Child (PID %d) finished\n", pid);
			}
		}
	}

	else if(argc > 1)																// If an argument is passed for number of children to create
	{
		limit = atoi(argv[1]);														// Convert argument string into a workable integer

		if (limit > 0 && limit <= 25)												// Assuming a negative integer is invalid, and maximum number of
		{																			// children is 25
			for(child = 0; child < limit; child++)
			{
				pid = fork();
				if(pid < 0)
				{
					fprintf(stderr, "Fork failed.\n");
					exit(1);
				}
				else if (pid == 0)													// Children will be assigned different programs to execute depending
				{																	// on the the order they were created (cylical between test1 and test5)
					pid = getpid();
					printf("Started child %d with pid %d\n", child + 1, pid);		// Just because the children are assigned these programs in this order
					sprintf(s, "./test%d", ((child % 5) + 1));						// does not mean they will execute in this order
					execlp(s, "", NULL);
				}
			}

			for (child = 0; child < limit; child++)									// Since child processes will be executing different code, we don't
			{																		// have to avoid the for loop in child processes, as well as look for
				pid = wait(NULL);													// a pid of 0
				printf("Child (PID %d) finished\n", pid);
			}
		}
		else																		// If the argument wasn't representable as an integer, or the
			printf("Incorrect argument.\n");										// argument was less than or equal to zero, then avoid an errror
	}

	return 0;
}