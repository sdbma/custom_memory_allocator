CC=g++
INCLUDE=-I$(PWD)/include
CFLAGS=-g -std=c++11 -I$(INCLUDE)

TARGET=test
SRC=./src
TESTS=./tests
BUILDDIR=./build
BINDIR=./bin
INCLUDE=./include
MKDIR_P = mkdir -p

all: $(BINDIR) $(BINDIR)/test

$(BINDIR)/test: $(BUILDDIR)/main.o $(BUILDDIR)/UnitTest.o $(BUILDDIR)/PoolAllocator.o $(BUILDDIR)/FreeListAllocator.o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRC)/%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: $(TESTS)/%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

$(BINDIR):
	$(MKDIR_P} $(OUTDIR)

clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/*

run: $(BINDIR)/testConv2D
	$(BINDIR)/testConv2D -f tests/tests.all

.PHONY: directories clean run
