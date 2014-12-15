/* Linux programozás
 * Vizi Gábor - HF
 */

 
// INCLUDES
#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "tcpserver.h"
#include "tcpclient.h"
#include "getipaddress.h"
#include "command.h"
#include "chat.h"
#include "global.h"
#include "log.h"
#include "datetime.h"


// DEFINES
#define DEFINE_TEXT_MENU	"Menu:\n"	\
				"[server] - Szerver\n"		\
				"[client] - Kliens\n"		\
				"[exit] - Kilépés\n"
							
#define PORT "1122"

#define DEFINE_CLIENTADDRESS	"192.168.211.128"
#define DEFINE_SERVERADDRESS	"localhost"


// GLOBAL VARIABLES
int sock;



// PROTOTYPES
int menu ( void );
int TCP_ServerInit ( void ); // const char *addresss
int TCP_ClientInit ( const char *addresss );


int main ( void )
{

	// Start events:

	DATETIME_Refresh();
	DATETIME_Printf();

	printf(DEFINE_TEXT_MENU);
	LOG_Open();



//	LOG_Write("$start\n");
//	DATETIME_Write2Log();

	LOG_WriteWithDateTime("program start");

	menu();	// loop

	LOG_WriteWithDateTime("program end");
	LOG_Close();

	return 0;
}



/*
 * @Function:	TODO: ...
 */
int menu ( void )
{
	char c;
	char string[20] = "\0";
	char address[20] = "localhost";	// azért ez a címe alapból, hogy lehessen használni a GetIpAddress-t


	while(1)
	{

		// Nem működik a fflush
//		fflush(stdin);
//		fflush(stdout);

		//scanf ("%19s",string);		// so-so
		//scanf ("%19s\n",string);		// so-so
		//scanf ("%19[^\n]",string);	// wrong
		//scanf ("%19\n",string);		// wrong
		//scanf ("%s",string);			// wrong
		//scanf ("%s\n",string);		// wrong

		// THIS IS OK
		scanf ("%19s",string);		// so-so
		while((c = getchar()) != '\n' && c != EOF);		// discard the character


		if ( strcmp(string, "server") == 0 )
		{
				//string =  "localhost" ;
				TCP_GetIpAddress(address);
				TCP_ServerInit ();	// TODO: delete DEFINE_SERVERADDRESS
		}
		else if ( strcmp(string, "client") == 0 )
		{
			printf("Kérlek írd be a szerver IP címét!\n");
			//fflush(stdin);
			//fflush(stdout);
			//gets(string); // !! IMPORTANT!! DANGEROUS!! UNSAFE!!
			//fgets (string , 20, stdin);	// DANGEROUS!! nem flusholódik ki az előző adat

			scanf ("%19s",address);	// "192.168.211.128"
			while((c = getchar()) != '\n' && c != EOF);		// discard the character

			//fflush(stdin);
			//fflush(stdout);
			printf("Cím feloldása...\n");
			TCP_GetIpAddress(address);
			printf("Szerver keresése...\n");
			TCP_ClientInit (address);
		}
		else if ( strcmp(string, "exit") == 0 )
		{
			return 1;
		}
		else
		{
			printf("Nincs ilyen parancs\n\n");
		} // end of last else

		printf(DEFINE_TEXT_MENU); // ujra kiírjuk a menüt



		/*
		// karakterbeolvasás
		fflush(stdin);
		fflush(stdout);
		// fflush();
		//c = getchar();
		//scanf("%c", &c);

		fflush(stdin);
		fflush(stdout);
		if (c == '\n' || c == '\r' || c == '\0' )
		{
			// DO NOTHING
		}
		else
		{
			switch (c)
			{
				case 'a':
					// TODO
					break;
				case 'b':
					//string =  "localhost" ;
					TCP_GetIpAddress(string);
					TCP_ServerInit ();	// TODO: delete DEFINE_SERVERADDRESS
					break;
				case 'c':
					printf("Kérlek írd be a szerver IP címét!\n");
					fflush(stdin);
					fflush(stdout);
					//gets(string); // !! IMPORTANT!! DANGEROUS!! UNSAFE!!
					//fgets (string , 20, stdin);	// DANGEROUS!! nem flusholódik ki az előző adat
					scanf ("%20s",string);	// "192.168.211.128"
					fflush(stdin);
					fflush(stdout);

					TCP_GetIpAddress(string);
					printf("Szerver keresése...\n");
					TCP_ClientInit (string);
					break;
				case 'x':
					return 1;
					break;
				default:
					printf("Nincs ilyen parancs\n\n");
					break;
			} // end of switch

			printf(DEFINE_TEXT_MENU); // ujra kiírjuk a menüt

		} // end of else
		*/
	} // end of while

} // end of menu

