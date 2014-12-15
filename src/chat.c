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
	  // 3. paraméter (warning volt rá):
	  // void *(*__start_routine) (void *),
	  // TODO: ellenőrizni, hogy jó-e így
	  if(pthread_create(&Thread_TCP, NULL, (void *)CHAT_TCPReceive, (void *)NULL))
	  {
		fprintf(stderr, "pthread_create (CHAT_TCPReceive)");
		exit(EXIT_FAILURE);
	  }

	  if(pthread_create(&Thread_STD, NULL, (void *)CHAT_STDINReceive , (void *)NULL))
	  {
		fprintf(stderr, "pthread_create (CHAT_STDReceive)");
		exit(EXIT_FAILURE);
	  }

	  // Szálakra várás
	  //pthread_join(Thread_STD, NULL);
	  // TODO: ez így nem a legjobb

	  GLOBAL_ChatExit_flag = 0;
	  while (1)
	  {
		  if ( GLOBAL_ChatExit_flag == 1 ) {
			  GLOBAL_ChatExit_flag = 0;

			  //pthread_join(Thread_TCP, NULL);

			  pthread_cancel(Thread_STD);
			  pthread_cancel(Thread_TCP);

			  //pthread_join(Thread_STD, NULL);
			  // return from CHAT_Loop()
			  // after this, close socket and others
			  return;
		  }
		  sleep(1);
	  }


}



void* CHAT_TCPReceive ( void )
{
	COMMAND_Message_t res;

	while (1)
	{
		// fogadjuk a beérkező csomagokat, és kiírjuk a tartalmát a képernyőre
		if((TCP_len = recv(csock, TCP_buf, sizeof(TCP_buf), 0)) > 0)
		{
			TCP_buf[TCP_len] = '\0';	// lezáró vég



			// parancs ellenőrzés
			/*
			if ( COMMAND_Check(TCP_buf,TCP_len) == COMMAND_MESSAGE_EXIT)
			{
				GLOBAL_ChatExit_flag = 1;
				while ( GLOBAL_ChatExit_flag == 1 )
				{
					//return;
					//pthread_exit(NULL);
				}
				pthread_exit(NULL);
				return NULL;
			}
			*/

			// ellenőrzés
			res = COMMAND_Check(TCP_buf,TCP_len);


			//if ( res == COMMAND_MESSAGE_EXIT ) 	// exit üzenet
			switch (res) {
				case COMMAND_MESSAGE_EXIT :
					{
						send(csock, TCP_buf, TCP_len, 0);
						GLOBAL_ChatExit_flag = 1;
						while ( GLOBAL_ChatExit_flag == 1 )
						{
							sleep(1);
						}
						pthread_exit(NULL);
						return NULL;
						break;
					}
				case COMMAND_MESSAGE_LOCAL :		// lokális parancs (most TCP: tehát most nem fordulhat elő)
					{
						// TODO:
						break;
					}
				case COMMAND_MESSAGE_REMOTE :		// távoli parancs (most TCP, tehát most végre kell hajtani)
					{
						// végrehajtás
						//TCP_buf[0] = '@';
						write(STDOUT_FILENO, "\e[32m", 5);	// zöld szöveg
						write(STDOUT_FILENO, TCP_buf, TCP_len);
						write(STDOUT_FILENO, "\e[0m", 4);	// visszaállítás

						COMMAND_RunCommand(TCP_buf,TCP_len);
						break;
					}

				case COMMAND_MESSAGE_OK :		// egyszerű üzenet, elküldés
					{
						write(STDOUT_FILENO, "\e[31m", 5);	// piros szöveg
						write(STDOUT_FILENO, TCP_buf, TCP_len);
						write(STDOUT_FILENO, "\e[0m", 4);	// visszaállítás
						break;
					}
				default:
					{
						// TODO:
						//printf("\e[31m");
						write(STDOUT_FILENO, "\e[31m", 5);	// piros szöveg
						//echo -e "\e[31mHello World\e[0m"
						//echo -e "\e[0mNormal Text"
						write(STDOUT_FILENO, TCP_buf, TCP_len);
						//printf("\e[0m");
						write(STDOUT_FILENO, "\e[0m", 4);	// visszaállítás
						break;
					}
			}	// end of switch


		}
	}
}


void* CHAT_STDINReceive ( void )
{
	COMMAND_Message_t res;

	while (1)
	{

		// az STDIN_FILENO-n érkező adatokat elküldjük a socketen keresztül
		if((STD_len = read(STDIN_FILENO, STD_buf, sizeof(STD_buf))) > 0)
		{
			STD_buf[STD_len] = '\0';	// lezáró vég

			// ellenőrzés
			res = COMMAND_Check(STD_buf,STD_len);


			//if ( res == COMMAND_MESSAGE_EXIT ) 	// exit üzenet
			switch (res) {
				case COMMAND_MESSAGE_EXIT :
					{
						send(csock, STD_buf, STD_len, 0);
						GLOBAL_ChatExit_flag = 1;
						while ( GLOBAL_ChatExit_flag == 1 )
						{
							//return;

						}
						pthread_exit(NULL);
						return NULL;
						break;
					}
				case COMMAND_MESSAGE_LOCAL :		// lokális parancs (most STD: tehát itt kell...)
					{
						COMMAND_RunCommand(STD_buf,STD_len);
						// elküldés
						//send(csock, STD_buf, STD_len, 0);
						break;
					}
				case COMMAND_MESSAGE_REMOTE :		// távoli parancs (most STD, tehát nem kell...)
					{
						// elküldés
						send(csock, STD_buf, STD_len, 0);
						break;
					}

				case COMMAND_MESSAGE_OK :		// egyszerű üzenet, elküldés
					{
						// elküldés
						send(csock, STD_buf, STD_len, 0);
						break;
					}
				default:
					{
						send(csock, STD_buf, STD_len, 0);
						break;
					}
			}	// end of switch


		} // end of if
	} // end of while(1)
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
