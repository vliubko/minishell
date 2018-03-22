
#include "stdio.h"

int 	main(int ac, char **av, char **env)
{
	while(*env)
		printf("%s\n",*env++);
	return (0);
}
