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


all: main.o window.o
	$(CC) $(CFLAGS) $(LIBS) window.o main.o -o $(EXE)

main.o: main.c hangman.h
	$(CC) $(CFLAGS) -c main.c

window.o: window.c window.h
	$(CC) $(CFLAGS) -c window.c

clean:
	rm -f *.o $(EXE) core


.PHONY: check-syntax

check-syntax:
	$(CC) $(CFLAGS) -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
