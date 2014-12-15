/*
 * command.c
 *
 *  Created on: Dec 13, 2014
 *      Author: fasten
 */

#include "command.h"
#include "log.h"

#include <unistd.h>	// for STDOUT_FILENO
#include <string.h>	// for strcmp

#include <stdlib.h>	// for system()


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

	char command[50];
	command[0] = '\0';

	/*
	// Ez jó, de más megvalósítás kell:
	if ( strcmp(buf,"command\n") == 0 )
	{
		write(STDOUT_FILENO, "Végrehajtok egy parancsot!\n", sizeof("Végrehajtok egy parancsot!\n"));

		system("echo \"parancsvégrehajtás bash-sel:\"\n");
		//system(buf);
		system(	"echo \"ls command:\n\"");
		system(	"echo \"\n\"");
		system(	"ls\n");

		system(	"echo \"itconfig command:\n\"");
		system(	"echo \"\n\"");
		system( "ifconfig\n");
	}*/

	//write(STDOUT_FILENO, "Végrehajtok egy parancsot!\n", sizeof("Végrehajtok egy parancsot!\n"));

	system("echo \"Parancsvégrehajtás BASH-sel:\"\n");

	//system(	"echo \""+buf+" command:\n\"");
	//system(	"echo \"\n\"");
	//system(buf+"\n");

	// strcpy
	strcpy(command,"echo \"");
	strcpy(command+strlen(command)," Parancs: ");
	strcpy(command+strlen(command),buf);
	strcpy(command+strlen(command),"\"");
	// strcat: nem jó így
//	strcat(command, "echo \"");
//	strcat(command, buf);
//	strcat(command, " command:\n\"");
	system(command);

	strcpy(command,buf);
	strcpy(command+strlen(command),"\n");
	//strcat(command,buf);
	//strcat(command,"\n");
	system(command);	// Execute the BASH command

	strcpy(command,"command: ");
	strcpy(command+strlen(command),buf);
	LOG_WriteWithDateTime(command);

}

