#ifndef sender_h
#define sender_h

int send_library(struct _node *n, char *payload, ssize_t payload_size);
void test_send(struct _node *n);

#endif
