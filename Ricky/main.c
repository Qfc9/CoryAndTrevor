#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#include "lib/graph.h"
#include "lib/listener.h"

int main(void) {
  /* code */
  graph g = graphCreate();
  char done[16];

  // Thread init
  pthread_t thread;
  pthread_attr_t  attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  pthread_create(&thread, &attr, listener, g);

  // Printing and waiting for an enter to end
  printf("Server Online...\n");
  printf("Press enter to close the server...\n");
  scanf("%s", done);

  // Killing all the threads
  pthread_kill(thread, SIGINT);

  // Freeing
  pthread_attr_destroy(&attr);


  graphDestroy(g);


  return 0;
}
