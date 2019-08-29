#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include "graph.h"
#include "sender.h"
#include "options.h"

int opt_send_library(graph g, char *filename){
  /* declare a file pointer */
  FILE    *infile;
  char    *buffer;
  long    numbytes;

  /* open an existing file for reading */
  infile = fopen(filename, "r");

  /* quit if the file does not exist */
  if(infile == NULL)
      return 1;

  /* Get the number of bytes */
  fseek(infile, 0L, SEEK_END);
  numbytes = ftell(infile);

  /* reset the file position indicator to
  the beginning of the file */
  fseek(infile, 0L, SEEK_SET);

  /* grab sufficient memory for the
  buffer to hold the text */
  buffer = (char*)calloc(numbytes, sizeof(char));

  /* memory error */
  if(buffer == NULL)
      return 1;

  /* copy all the text into the buffer */
  fread(buffer, sizeof(char), numbytes, infile);
  fclose(infile);

  return send_library(g->nodes, buffer, numbytes);
}
