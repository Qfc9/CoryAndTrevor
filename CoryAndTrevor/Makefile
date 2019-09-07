CPPFLAGS += -Wall -Wextra -Wpedantic
CPPFLAGS += -D_XOPEN_SOURCE -pthread -std=c11 -lm -lc  -DDEBUG -g -ldl
ARFLAGS += -U

DEBUG = -DDEBUG -g

BINS = coryAndTrevor

FILES = main.o lib/ping.o lib/listener.o
all: build

.PHONY: all

# debug: CFLAGS += -DDEBUG -g
debug:  $(FILES)
	gcc -o $(BINS) $(FILES) $(CPPFLAGS) $(CFLAGS)
	$(MAKE) clean

profile: CFLAGS += -pg
profile: CPPFLAGS += -pg
profile: $(FILES)
	gcc -o $(BINS) $(FILES) $(CPPFLAGS) $(CFLAGS)
	$(MAKE) clean

build: $(FILES)
	gcc -o $(BINS) $(FILES) $(CPPFLAGS) $(CFLAGS)
	$(MAKE) clean

clean:
	$(RM) *.o

cleanAll:
	$(RM) $(BINS) *.o
