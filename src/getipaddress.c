/* getipaddr.c
 *
 * Internetes névfeloldás példa. A paraméterként kapott hosztnevet
 * IP címmé alakítja. Támogatja az IPv4 és IPv6 címeket is.
 *
 */
#include "getipaddress.h"


#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>


int TCP_GetIpAddress ( char *string )
{
  struct addrinfo hints;
  struct addrinfo* res;
  struct addrinfo* p;
  int err;
  char ips[INET6_ADDRSTRLEN];

  if( string == NULL )
  {
    printf("GetIpAddress string fail!");
    return -1;
  }

  // kitöltjük a hints struktúrát
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  // végezzük el a névfeloldást
  err = getaddrinfo( string, NULL, &hints, &res);
  if(err != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    return -1;
  }

  // járjuk be egy ciklusban a kapott láncolt listát (ai_next)
  for(p = res; p != NULL; p = p->ai_next)
  {
    // döntsük el, hogy IPv4 vagy IPv6 cím van a struktúrában, annak megfelelően írjuk ki a tartalmát
    if(p->ai_family == AF_INET)
    {
      if(inet_ntop(AF_INET, &((struct sockaddr_in*)(p->ai_addr))->sin_addr, ips, sizeof(ips)) != NULL)
      {
        printf("IP: %s\n", ips);
        strcpy(string,ips);
      }
    }
    else if(p->ai_family == AF_INET6)
    {
      if(inet_ntop(AF_INET6, &((struct sockaddr_in6*)(p->ai_addr))->sin6_addr, ips, sizeof(ips)) != NULL)
      {
        printf("IP: %s\n", ips);
        strcpy(string,ips);
      }
    }
  }

  // szabadítsuk fel a láncolt listát
  freeaddrinfo(res);

  return 0;
}
