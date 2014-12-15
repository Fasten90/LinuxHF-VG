/*
 * log.c
 *
 *  Created on: Dec 15, 2014
 *      Author: fasten
 */


#include "log.h"
#include "datetime.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>



// GLOBAL VARIABLES
int fd;



int LOG_Open ( void )
{



    // megnyitjuk a fájlt, ha nincs, létrehozzuk a 644 jogosultsággal
    //fd = open ( "LOG.log, O_WRONLY | O_CREAT | O_TRUNC, 0644 );
	//  O_TRUNC Ha az állomány létezik, akkor tartalma törlődik, és a mérete 0 lesz.
    fd = open ( "LOG.log", O_RDWR | O_APPEND | O_NONBLOCK | O_CREAT, 0644 );
    if ( fd < 0 ) { // hibával tér vissza (negatív érték)
		perror ( "open" );
		return -1;
    }
    return 0;

}



int LOG_Write ( char *s )
{

	int len = strlen(s);

	if (len == 0 )
	{
		perror ("0 length string!");
		return -1;
	}

    // write () // utolsó paraméter: hány karaktert írjon ki
    if (write ( fd, s, len ) != len) {
		perror ( "write");
		return -1;
    }

    //     close(fd);    // bezárjuk
    return 0;

}



int LOG_WriteWithDateTime (char *s )
{

	char datetime[30];

	int len = strlen(s);

	if (len == 0 )
	{
		perror ("0 length string!");
		return -1;
	}

	DATETIME_Write2String(datetime);

	write (fd,datetime,strlen(datetime));

	write (fd," $",strlen(" $"));

    // write () // utolsó paraméter: hány karaktert írjon ki
    if (write ( fd, s, len ) != len) {
		perror ( "write");
		return -1;
    }

    write (fd,"\n",strlen("\n"));

    //     close(fd);    // bezárjuk
    return 0;

}


int LOG_Close ( void )
{
    close(fd);    // bezárjuk
    return 0;
}



int LOG_Read (int argc, char* argv[])
{
	/*
   if (argc < 2) {
       printf("USAGE: %s filename\n", argv[0]);
       return 1;
   }
   */

	/*
   int fd;
   fd = open(argv[1], O_RDONLY);
   if ( fd < 0 ) {
     perror ( "open" );
     return -1;
   }
	*/

   char buf[200];
   if ( read( fd, buf, sizeof(buf)) == -1) {
     perror ( "read" );
     return -1;
   }

   printf("%s\n",buf);

   //close(fd);
   return 0;

}


