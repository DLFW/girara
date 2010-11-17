# See LICENSE file for license and copyright information

VERSION = 0.0.0

# paths
PREFIX ?= /usr

# libs
GTK_INC = $(shell pkg-config --cflags gtk+-2.0)
GTK_LIB = $(shell pkg-config --libs gtk+-2.0)

INCS = -I. -I/usr/include ${GTK_INC}
LIBS = -lc ${GTK_LIB}

# flags
CFLAGS += -std=c99 -pedantic -Wall -Wextra -fPIC $(INCS)

# linker flags
LDFLAGS += -fPIC

# debug
DFLAGS = -O0 -g

# compiler
CC ?= gcc

# strip
SFLAGS = -s
