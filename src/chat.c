/*
 * chat.c
 *
 *  Created on: Dec 13, 2014
 *      Author: fasten
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "chat.h"
#include "global.h"
#include "command.h"

#include <pthread.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdlib.h>

#include <unistd.h>	// for STDOUT_FILENO

#include <stddef.h>



// GLOBAL VARIABLES
int ssock, csock;
char TCP_buf[256];
char STD_buf[256];
int TCP_len;
int STD_len;


//int value = 0;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cvar = PTHREAD_COND_INITIALIZER;


void CHAT_Loop ( void )
{
	  pthread_t Thread_TCP;
	  pthread_t Thread_STD;

	// Szálak létrehozása

	// Szálakra várás
	  if(pthread_create(&Thread_TCP, NULL, CHAT_TCPReceive, NULL))
	  {
		fprintf(stderr, "pthread_create (CHAT_TCPReceive)");
		exit(EXIT_FAILURE);
	  }

	  if(pthread_create(&Thread_STD, NULL, CHAT_STDINReceive , NULL))
	  {
		fprintf(stderr, "pthread_create (CHAT_STDReceive)");
		exit(EXIT_FAILURE);
	  }

	  pthread_join(Thread_STD, NULL);



}



void CHAT_TCPReceive ( void )
{
	while (1)
	{
		// fogadjuk a beérkező csomagokat, és kiírjuk a tartalmát a képernyőre
		if((TCP_len = recv(csock, TCP_buf, sizeof(TCP_buf), 0)) > 0)
		{
			if ( COMMAND_Check(TCP_buf,TCP_len) == COMMAND_MESSAGE_EXIT) return;
			// TODO:
			//printf("\e[31m");
			write(STDOUT_FILENO, "\e[31m", 5);	// piros szöveg
			//echo -e "\e[31mHello World\e[0m"
			//echo -e "\e[0mNormal Text"
			write(STDOUT_FILENO, TCP_buf, TCP_len);
			//printf("\e[0m");
			write(STDOUT_FILENO, "\e[0m", 4);	// visszaállítás
		}
	}
}


void CHAT_STDINReceive ( void )
{
	while (1)
	{
		// az STDIN_FILENO-n érkező adatokat elküldjük a socketen keresztül
		if((STD_len = read(STDIN_FILENO, STD_buf, sizeof(STD_buf))) > 0)
		{
			if ( COMMAND_Check(STD_buf,STD_len) == COMMAND_MESSAGE_EXIT) return;
			send(csock, STD_buf, STD_len, 0);
		}
	}
}





/*
void* alarm_thr(void* data)
{
  int new_value;
  int old_value = 0;
  while(1)
  {
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cvar, &mutex);
    new_value = value;
    pthread_mutex_unlock(&mutex);

    if((new_value >= 90) && (old_value < 90))
    {
      printf("Bumm, the end!\n");
    }
    else if((new_value >= 60) && (old_value < 60))
    {
      printf("Meleg a helyzet!\n");
    }
    else if((new_value >= 30) && (old_value < 30))
    {
      printf("Érdemes lenne odafigyelni!\n");
    }
    old_value = new_value;
  }
  return NULL;
}

void* measure_thr(void* data)
{
  int i;
  for(i = 0; i <= 100; i += 10)
  {
    pthread_mutex_lock(&mutex);
    value = i;
	pthread_cond_broadcast(&cvar);
    pthread_mutex_unlock(&mutex);

    sleep(1);

  }
  return NULL;
}

int main()
{
  pthread_t th_m;
  pthread_t th_a;

  printf("Program indul...\n");
  if(pthread_create(&th_a, NULL, alarm_thr, NULL))
  {
    fprintf(stderr, "pthread_create (alarm)");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&th_m, NULL, measure_thr, NULL))
  {
    fprintf(stderr, "pthread_create (measure)");
    exit(EXIT_FAILURE);
  }
  pthread_join(th_m, NULL);
  printf("Program vége.\n");
  exit(EXIT_SUCCESS);
}

*/
