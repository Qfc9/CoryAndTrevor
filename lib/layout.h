#ifndef layout_h
#define layout_h

#include <stdlib.h>

struct base_layout {
  unsigned int version : 4;
  unsigned int type : 4;
  size_t payload_size : 32;
} base_layout;


#endif
