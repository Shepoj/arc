CC = gcc
CFLAGS = -Wall -I$(INCDIR) -g

HOMEDIR = ../..
INCDIR = $(HOMEDIR)/include
SRCDIR = $(HOMEDIR)/src
OBJDIR = $(HOMEDIR)/obj

BIN = codegentest

all: $(BIN)

.PHONY: all test clean

$(BIN): codegentest.c $(OBJDIR)/codegen.o $(INCDIR)/codegen.h $(OBJDIR)/ast.o $(OBJDIR)/tabsymb.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

test:
	./$(BIN)

clean:
	rm -f *~ 
