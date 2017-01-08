C = gcc
PKGCONFIG=pkg-config
NULL=
EXE=hangman

CWD := $(shell pwd)
# Platform
UNAME := $(shell $(CC) -dumpmachine 2>&1 | grep -E -o "linux|darwin")

## Silent by default
V =
ifeq ($(strip $(V)),)
        E = @echo
        Q = @
else
        E = @\#
        Q =
endif
export E Q


ifeq ($(UNAME), linux)
OSFLAGS = -DLINUX
DEBUG = -ggdb
else ifeq ($(UNAME), darwin)
OSFLAGS = -DMACOSX
DEBUG = -g
else ifeq ($(UNAME), solaris)
OSFLAGS = -DSOLARIS
DEBUG = -g
endif

EXTRA_CFLAGS := \
	-DTIOCGWINSZ \
        -Wall -Wextra -pedantic \
        $(NULL)

CFLAGS := $(DEBUG) $(EXTRA_CFLAGS) $(OSFLAGS)
LIBS := -lncurses\
        $(NULL)


all: main.o window.o game.o display.o util.o
	$(CC) $(CFLAGS) $(LIBS) window.o  \
				main.o    \
				game.o    \
				display.o \
				util.o    \
				-o $(EXE)

main.o: main.c hangman.h
	$(CC) $(CFLAGS) -c main.c

window.o: window.c window.h hangman.h
	$(CC) $(CFLAGS) -c window.c

game.o: game.c game.h hangman.h
	$(CC) $(CFLAGS) -c game.c

display.o: display.c display.h hangman.h
	$(CC) $(CFLAGS) -c display.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:
	rm -f *.o $(EXE) core


.PHONY: check-syntax

check-syntax:
	$(CC) $(CFLAGS) -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
