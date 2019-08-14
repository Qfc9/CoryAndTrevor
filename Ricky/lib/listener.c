#define _GNU_SOURCE

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <ifaddrs.h>
#include <netinet/in.h>

#include "util.h"
#include "listener.h"

#define PORT     8080
#define MAXLINE 1024

// Opens a socket and listens for incoming connections, spins off new threads for new connections
void *listener(void *data)
{
  char buffer[100];
  char *message = "Hello Client";
  int listenfd, len;
  struct sockaddr_in servaddr, cliaddr;
  bzero(&servaddr, sizeof(servaddr));

  // Create a UDP Socket
  listenfd = socket(AF_INET, SOCK_DGRAM, 0);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);
  servaddr.sin_family = AF_INET;

  // bind server address to socket descriptor
  bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

  //receive the datagram
  len = sizeof(cliaddr);
  int n = recvfrom(listenfd, buffer, sizeof(buffer),
          0, (struct sockaddr*)&cliaddr,&len); //receive message from server
  buffer[n] = '\0';
  puts(buffer);

  // send the response
  sendto(listenfd, message, MAXLINE, 0,
        (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 

    return 0;
}
