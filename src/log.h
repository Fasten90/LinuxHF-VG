/*
 * log.h
 *
 *  Created on: Dec 15, 2014
 *      Author: fasten
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

// GLOBAL VARIABLES
extern int fd;

// PROTOTYPES
int LOG_Open ( void );
int LOG_Write ( char *s );
int LOG_WriteWithDateTime (char *s );
int LOG_Close ( void );
int LOG_Read (int argc, char* argv[]);




#endif /* SRC_LOG_H_ */
