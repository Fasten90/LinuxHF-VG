/*
 * command.c
 *
 *  Created on: Dec 13, 2014
 *      Author: fasten
 */

#include "command.h"

#include <unistd.h>	// for STDOUT_FILENO



COMMAND_Check ( const char *buf, const int len);


COMMAND_Check ( const char *buf, const int len)
{
	// TODO:
	if ( strcmp(buf,"exit\n") == 0 ) // it is equal
	{
		//printf("BLAAAAAAAAAAAAAAAAA\n");
		write(STDOUT_FILENO, "BLAAAAAAAAAAAAAAAA\n", sizeof("BLAAAAAAAAAAAAAAAA\n"));
	}


}
