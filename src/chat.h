/*
 * chat.h
 *
 *  Created on: Dec 13, 2014
 *      Author: fasten
 */

#ifndef SRC_CHAT_H_
#define SRC_CHAT_H_


// GLOBAL VARIABLES

extern int ssock, csock;
extern char TCP_buf[];
extern char STD_buf[];
extern int TCP_len;
extern int STD_len;

// PROTOTYPES
void CHAT_Loop ( void );
void* CHAT_TCPReceive ( void );
void* CHAT_STDINReceive ( void );



#endif /* SRC_CHAT_H_ */
