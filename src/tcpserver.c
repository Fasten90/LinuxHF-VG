/* tcpszerver.c
 *
 * Egyszerű TCP szerver példa. Képes egy kapcsolat fogadására és
 * kiírja a képernyőre a kapott adatokat.
 *
 */

#include "tcpserver.h"
#include "command.h"
#include "chat.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#define PORT "1122"


extern int csock;
extern int ssock;



int TCP_ServerInit ( void )
{
  struct addrinfo hints;
  struct addrinfo* res;
  int err;
  struct sockaddr_in6 addr;
  socklen_t addrlen;
  char ips[NI_MAXHOST];
  char servs[NI_MAXSERV];

  int reuse;

  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;

  err = getaddrinfo(NULL, PORT, &hints, &res);
  if(err != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    return -1;
  }
  if(res == NULL)
  {
    return -1;
  }

  // Létrehozzuk a server socketet getaddrinfo() válasza alapján
  ssock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(ssock < 0)
  {
    perror("socket");
    return 1;
  }

  // Engedélyezzük a REUSE-t (SO_REUSEADDR). Socket level (SOL_SOCKET)
  reuse = 1;
  setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  // Címhez kötjük a server socketet getaddrinfo() válasza alapján
  if(bind(ssock, res->ai_addr, res->ai_addrlen) < 0)
  {
    perror("bind");
    return 1;
  }

  // Bekapcsoljuk a kapcsolódásra való varakozást.
  if(listen(ssock, 5) < 0)
  {
    perror("listen");
    return 1;
  }
  else
  {
	  printf("Várakozás a kliens csatlakozására.\n");
  }

  // Felszabadítjuk a getadrrinfo() által generált láncolt listát.
  // A továbbiakban nem lesz rá szükségünk
  freeaddrinfo(res);

  // Cím hosszának beállítása sizeof()val
  addrlen = sizeof(addr);
  // Fogadjuk a kapcsolodasokat.

  csock = accept(ssock, (struct sockaddr*)&addr, &addrlen);

  // próbáljuk meg kideríteni a kapcsolódó nevét
  if(getnameinfo((struct sockaddr*)&addr, addrlen,
	ips, sizeof(ips), servs, sizeof(servs), 0) == 0)
  {
	printf("Kapcsolódás: %s:%s\n", ips, servs);
  }

  CHAT_Loop();

  printf("Kapcsolat zárása.\n");
  // lezárjuk a kliens socketet
  close(csock);
  /*
  while((csock = accept(ssock, (struct sockaddr*)&addr, &addrlen)) >= 0)
  {
    // próbáljuk meg kideríteni a kapcsolódó nevét
    if(getnameinfo((struct sockaddr*)&addr, addrlen,
      ips, sizeof(ips), servs, sizeof(servs), 0) == 0)
    {
      printf("Kapcsolódás: %s:%s\n", ips, servs);
    }

    CHAT_Loop();

    printf("Kapcsolat zárása.\n");
    // lezárjuk a kliens socketet
    close(csock);
  }
  */

  // lezárjuk a szerver socketet
  close(ssock);

  return 0;
}

