# Makefile
CC=g++
CFLAGS=-Og -I ../ -std=c++2a

all: xormake

clean:
	rm -rf xormake

ODIR=obj

_OBJ = xor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

xormake: 
	$(CC) -o $@ ../artificialIntelligence/neuralNetworks/xor.cpp $(CFLAGS)

.PHONY: clean