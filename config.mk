# See LICENSE file for license and copyright information

VERSION = 0.0.0
SOMAJOR = 0
SOMINOR = 0
SOVERSION = ${SOMAJOR}.${SOMINOR}

# paths
PREFIX ?= /usr

GIRARA_GTK_VERSION ?= 2

# libs
GTK_INC = $(shell pkg-config --cflags gtk+-${GIRARA_GTK_VERSION}.0)
GTK_LIB = $(shell pkg-config --libs gtk+-${GIRARA_GTK_VERSION}.0)

INCS = ${GTK_INC}
LIBS = ${GTK_LIB}

# flags
CFLAGS += -std=c99 -pedantic -Wall -Wextra -fPIC $(INCS)

# linker flags
LDFLAGS += -fPIC

# debug
DFLAGS = -O0 -g

# compiler
CC ?= gcc

# strip
SFLAGS ?= -s

# set to something != 0 if you want verbose build output
VERBOSE ?= 0
