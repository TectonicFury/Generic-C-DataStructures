CFLAGS = -Wall -std=c11
OBJECTS = Test.o

test: $(OBJECTS)
	clang -o test $(OBJECTS) $(CFLAGS)
Test.o: Test.c bst.h
	clang -c Test.c $(CFLAGS)
