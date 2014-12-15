/*
 * datetime.c
 *
 *  Created on: Dec 15, 2014
 *      Author: fasten
 */


#include "datetime.h"
#include "log.h"

#include <stddef.h>	// for time_t
#include <time.h>	// for tm, ...
#include <stdio.h>	// for string function


/*
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
 */

time_t t;
struct tm tm;


void DATETIME_Refresh ( void )
{
	t = time(NULL);
	tm = *localtime(&t);
}


void DATETIME_Printf ( void )
{
	printf("Dátum: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void DATETIME_Write2Log ( void )
{
	char string[30];


	sprintf(string, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	LOG_Write ( string );
	//fprintf(fd, "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	// THIS WRONG! segmentation fault! nincs lezáró

	//printf("Dátum: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void DATETIME_Write2String ( char *string )
{
	DATETIME_Refresh();
	sprintf(string, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

}


/*
Use time() and localtime() to get the time:

time_t t = time(NULL);
struct tm tm = *localtime(&t);

printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

*/

