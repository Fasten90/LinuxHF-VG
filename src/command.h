/*
 * command.h
 *
 *  Created on: Dec 13, 2014
 *      Author: fasten
 */

#ifndef SRC_COMMAND_H_
#define SRC_COMMAND_H_


typedef int COMMAND_Message_t;



#define COMMAND_MESSAGE_OK			(COMMAND_Message_t)0
#define COMMAND_MESSAGE_EXIT		(COMMAND_Message_t)1
#define COMMAND_MESSAGE_LOCAL		(COMMAND_Message_t)2
#define COMMAND_MESSAGE_REMOTE		(COMMAND_Message_t)3

//#define COMMAND_MESSAGE_EXIT	1
//#define COMMAND_MESSAGE_OK		0


int COMMAND_Check ( const char *buf, const int len);
void COMMAND_RunCommand( char *buf, int len);


#endif /* SRC_COMMAND_H_ */
