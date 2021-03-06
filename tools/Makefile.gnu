CFLAGS += -g -DDEBUG -DUNICODE -DUTF8 -I../src
LIBPHORWARD = ../src/libphorward.a

PLEX		= ../run/plex
PPARSE		= ../run/pparse
PREGEX		= ../run/pregex
PVM			= ../run/pvm

all: $(PLEX) $(PPARSE) $(PREGEX) $(PVM)

clean:
	-rm plex.o
	-rm pparse.o
	-rm pregex.o
	-rm ppgram2c.o
	-rm pvm.o
	-rm util.o
	-rm $(PLEX) $(PPARSE) $(PREGEX) $(PPGRAM2C) $(PVM)

$(PLEX): plex.o util.o $(LIBPHORWARD)
	$(CC) -o $@ $+

$(PPARSE): pparse.o util.o $(LIBPHORWARD)
	$(CC) -o $@ $+

$(PREGEX): pregex.o util.o $(LIBPHORWARD)
	$(CC) -o $@ $+

$(PVM): pvm.o util.o $(LIBPHORWARD)
	$(CC) -o $@ $+

