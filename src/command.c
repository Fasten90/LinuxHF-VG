/*
 * command.c
 *
 *  Created on: Dec 13, 2014
 *      Author: fasten
 */

#include "command.h"

#include <unistd.h>	// for STDOUT_FILENO
#include <string.h>	// for strcmp




COMMAND_Message_t COMMAND_Check ( const char *buf, const int len)
{
	// TODO:
	if ( strcmp(buf,"exit\n") == 0 ) // it is equal
	{
		//printf("BLAAAAAAAAAAAAAAAAA\n");
		write(STDOUT_FILENO, "Kilépés!\n", sizeof("Kilépés!\n"));
		return COMMAND_MESSAGE_EXIT;
	}


	return COMMAND_MESSAGE_OK;
}


