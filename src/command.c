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
	// if ( strcmp(buf,"string") == 0 ) // it is equal

	if ( strcmp(buf,"exit\n") == 0 )		// exit\n
	{
		write(STDOUT_FILENO, "Kilépés!\n", sizeof("Kilépés!\n"));
		return COMMAND_MESSAGE_EXIT;
	}

	else if ( buf[0] == '@' )					// start with '@'
	{
		write(STDOUT_FILENO, "Lokális parancs!\n", sizeof("Lokális parancs!\n"));
		return COMMAND_MESSAGE_LOCAL;
	}

	else if ( buf[0] == '#' )					// start with '#'
	{
		write(STDOUT_FILENO, "Távoli parancs!\n", sizeof("Távoli parancs!\n"));
		return COMMAND_MESSAGE_REMOTE;
	}


	return COMMAND_MESSAGE_OK;
}




void COMMAND_RunCommand ( char *buf, int len)
{
	strcpy ( buf, &buf[1] );
	if ( strcmp(buf,"command\n") == 0 )
	{
		write(STDOUT_FILENO, "Végrehajtok egy parancsot!\n", sizeof("Végrehajtok egy parancsot!\n"));
	}
}

