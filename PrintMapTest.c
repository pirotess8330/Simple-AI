#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Environment.h"

int main()
{
	struct Environment* environ;
	environ = createEnvironment("freakyMap");
	printMap(environ);
	return 0;
}
