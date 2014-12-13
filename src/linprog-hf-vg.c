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


// DEFINES
#define DEFINE_TEXT_MENU	"Menu:\n"	\
				"[a] - Function1\n"		\
				"[b] - Szerver\n"		\
				"[c] - Kliens\n"		\
				"[x] - Kilépés\n"
							
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

	menu();

	return 0;
}



/*
 * @Function:	TODO: ...
 */
int menu ( void )
{
	char c;
	char string[20];
	
	printf(DEFINE_TEXT_MENU);

	while(1)
	{

		// karakterbeolvasás
		fflush(stdin);
		fflush(stdout);
		// fflush();
		//c = getchar();
		scanf("%c", &c);
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
					TCP_ServerInit ();	// TODO: delete DEFINE_SERVERADDRESS
					break;
				case 'c':
					printf("Kérlek írd be a szerver IP címét!\n");
					//fflush(stdin);
					//fflush(stdout);
					//gets(string); // !! IMPORTANT!! DANGEROUS!! UNSAFE!!
					//fgets (string , 20, stdin);	// DANGEROUS!! nem flusholódik ki az előző adat
					scanf ("%20s",string);	// "192.168.211.128"

					TCP_GetIpAddress(string);
					//fflush(stdin);
					//fflush(stdout);
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
	} // end of while

} // end of menu

