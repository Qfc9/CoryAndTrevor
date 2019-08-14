// udp client driver program
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#include "lib/ping.h"

#define PORT 8080
#define MAXLINE 1000

// Driver code
int main(void)
{
  char done[16];

  // Thread init
  pthread_t thread;
  pthread_attr_t  attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  pthread_create(&thread, &attr, ping, NULL);

  // Printing and waiting for an enter to end
  printf("Client Online...\n");
  printf("Press enter to close the client...\n");
  scanf("%s", done);

  // Killing all the threads
  pthread_kill(thread, SIGINT);

  // Freeing
  pthread_attr_destroy(&attr);

  return 0;
}
