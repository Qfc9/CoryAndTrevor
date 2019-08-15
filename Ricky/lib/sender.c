#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../../lib/layout.h"
#include "graph.h"

void test_send(struct _node *n){
  // Socket setup
  struct addrinfo hints = {0};
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  // Getting socket info
  struct addrinfo *results;
  int err = getaddrinfo(n->data.ip_addr, n->data.port, &hints, &results);
  if(err != 0) {
      // fprintf(stderr, "Could not get address: %s\n", gai_strerror(err));
      return;
  }

  // Establishing the socket
  int sd = socket(results->ai_family, results->ai_socktype, 0);
  if(sd < 0) {
      perror("Could not establish socket");
      freeaddrinfo(results);
      return;
  }

  // Adding socket option for faster binding
  int yes = 1;
  err = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  if(err < 0) {
      perror("Unable to alter socket options");
      close(sd);
      return;
  }

  // Attempting to connect to dispatcher
  err = connect(sd, results->ai_addr, results->ai_addrlen);
  if(err < 0)
  {
      perror("Could not bind socket");
      close(sd);
      freeaddrinfo(results);
      return;
  }

  // Freeing the results
  freeaddrinfo(results);

  struct base_layout payload;
  payload.version = 1;
  payload.type = 1;
  payload.payload_size = 0;

  send(sd, &payload, sizeof(payload), 0);

  close(sd);
}
