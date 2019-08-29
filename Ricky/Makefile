CPPFLAGS += -Wall -Wextra -Wpedantic
CPPFLAGS += -D_XOPEN_SOURCE -pthread -std=c11 -lm -lc  -DDEBUG -g
ARFLAGS += -U

DEBUG = -DDEBUG -g

BINS = ricky

FILES = main.o lib/graph.o lib/listener.o lib/util.o ../lib/layout.o lib/sender.o lib/options.o
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
	$(RM) *.o lib/*.o ../lib/*.o

cleanAll:
	$(RM) $(BINS) *.o lib/*.o ../lib/*.o
