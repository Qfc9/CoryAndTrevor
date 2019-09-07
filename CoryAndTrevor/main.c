// udp client driver program
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "lib/ping.h"
#include "lib/listener.h"

// Driver code
int main(void)
{
  srand((unsigned)time(NULL));
  char done[16];

  // Thread init
  char port[5] = "";
  pthread_t thread_ping;
  pthread_t thread_listener;
  pthread_attr_t  attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  pthread_create(&thread_listener, &attr, listener, port);

  while(strncmp(port, "", 1) == 0){
    sleep(1);
  }

  pthread_create(&thread_ping, &attr, ping, &port);

  // Printing and waiting for an enter to end
  printf("Client Online...\n");
  printf("Press enter to close the client...\n");
  scanf("%s", done);

  // Killing all the threads
  pthread_kill(thread_listener, SIGINT);
  pthread_kill(thread_ping, SIGINT);

  // Freeing
  pthread_attr_destroy(&attr);

  return 0;
}
