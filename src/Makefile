CFLAGS = -Wall -g -std=c11 -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
CFLAGS1 = -Wall -g -std=c11 -fsanitize=address

all: test_bst test_rbt tale_freq

test_bst: Test_bst.o
	clang -o test_bst Test_bst.o $(CFLAGS1)
Test_bst.o: Test_bst.c bst.h
	clang -c Test_bst.c $(CFLAGS)

test_rbt: Test_rbt.o
	clang -o test_rbt Test_rbt.o $(CFLAGS1)
Test_rbt.o: Test_rbt.c rbt.h
	clang -c Test_rbt.c $(CFLAGS)

tale_freq: tale_freq.o
	clang -o tale_freq tale_freq.o $(CFLAGS1)
tale_freq.o: tale_freq.c rbt.h
	clang -c tale_freq.c $(CFLAGS)

clean:
	rm test_* *.o
