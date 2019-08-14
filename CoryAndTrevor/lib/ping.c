// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 8080
#define MAXLINE 1000

// Driver code
void *ping(void *data)
{
    char buffer[100];
    char *message = "Hello Server";
    int sockfd, n;
    struct sockaddr_in servaddr, cliaddr;

    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    while (1) {
      sleep(3);
      // create datagram socket
      sockfd = socket(AF_INET, SOCK_DGRAM, 0);

      // connect to server
      if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
      {
          printf("\n Error : Connect Failed \n");
          exit(0);
      }

      // request to send datagram
      // no need to specify server address in sendto
      // connect stores the peers IP and port
      sendto(sockfd, data, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
      
      // close the descriptor
      close(sockfd);    }
}
