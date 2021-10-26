CFLAGS = -Wall -g -std=c11 -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
CFLAGS1 = -Wall -g -std=c11 -fsanitize=address
OBJECTS = Test_bst.o

test_bst: $(OBJECTS)
	clang -o test_bst $(OBJECTS) $(CFLAGS1)
Test_bst.o: Test_bst.c bst.h
	clang -c Test_bst.c $(CFLAGS)

test_rbt: Test_rbt.o
	clang -o test_rbt Test_rbt.o $(CFLAGS1)
Test_rbt.o: Test_rbt.c rbt.h
	clang -c Test_rbt.c $(CFLAGS)
clean:
	rm test_* *.o
