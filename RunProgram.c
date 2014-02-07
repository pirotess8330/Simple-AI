#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WumpusAgent.h"
#include "Environment.h"
#include "Directions.h"

void usage();

int main(int argc, char *argv[])
{
	char* filename;
	int numberOfAgents;
	FILE *in;

	if(argc != 3)
	{
		usage();
	}

	filename = argv[1];
	numberOfAgents = atoi(argv[2]);
	if(numberOfAgents > 10)
	{
		usage();
	}

	in = fopen(filename, "r");
   	if (in == NULL)
   	{
       fprintf(stderr, "%s: '%s' not found!\n", argv[0], filename);
   	   exit(-1);
   	}

   	struct Environment* environ;
	environ = createEnvironment(filename);

	return 0;
}

void usage()
{
	printf("Usage: RunProgram 'filename' numberOfAgents(less than 10)\n");
	exit(-1);
}

