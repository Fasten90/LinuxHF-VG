/* tcpkliens.c
 *
 * Egyszerű TCP kliens példa. A program kapcsolódik a paraméterként
 * kapott szerverhez és elküldi a bemenetén kapott szöveget.
 *
 */

#include "tcpclient.h"
#include "command.h"
#include "chat.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT "1122"

int TCP_ClientInit( char* address)
{
  struct addrinfo hints;
  struct addrinfo* res;
  int err;

  extern int csock;
  extern char buf[];
  extern int len;

  if ( address == NULL )
  {
    //printf("Használat:  <szerver>\n");
	perror("Address is null!");
    return 1;
  }

  // kitöltjük a hints struktúrát
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  // végezzük el a névfeloldást
  err = getaddrinfo(address, PORT, &hints, &res);
  if(err != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    return -1;
  }
  if(res == NULL)
  {
    return -1;
  }

  // létrehozzuk a kliens socketet
  csock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(csock < 0)
  {
    perror("socket");
    return -1;
  }

  // Kapcsolodunk a szerverhez.
  if(connect(csock, res->ai_addr, res->ai_addrlen) < 0)
  {
    perror("connect");
    return -1;
  }
  else	// sikeres csatlakozás
  {
	  printf("Sikeres csatlakozás!\n");
  }

	/*
	// az STDIN_FILENO-n érkező adatokat elküldjük a socketen keresztül
	while((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
	{

		send(csock, buf, len, 0);

		COMMAND_Check(buf,len);
	}
	*/

  /*
	while (1)
	{

//		// fogadjuk a beérkező csomagokat, és kiírjuk a tartalmát a képernyőre
//		if((len = recv(csock, buf, sizeof(buf), 0)) > 0)
//		{
//				COMMAND_Check(buf,len);
//				// TODO:
//				//printf("\e[31m");
//				write(STDOUT_FILENO, "\e[31m", 5);	// piros szöveg
//				//echo -e "\e[31mHello World\e[0m"
//				//echo -e "\e[0mNormal Text"
//				write(STDOUT_FILENO, buf, len);
//				//printf("\e[0m");
//				write(STDOUT_FILENO, "\e[0m", 4);	// visszaállítás
//		}


		// az STDIN_FILENO-n érkező adatokat elküldjük a socketen keresztül
		if((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
		{
			send(csock, buf, len, 0);
		}
	} // end of while
	*/

  	  CHAT_Loop();

  // lezárjuk a szerver socketet
  close(csock);

  // szabadítsuk fel a láncolt listát
  freeaddrinfo(res);

  return 0;
}
