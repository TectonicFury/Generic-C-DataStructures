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

seq_search: seq_search_test.o
	clang -o seq_search seq_search_test.o $(CFLAGS1)
seq_search_test.o: seq_search_test.c sequential_search.h
	clang -c seq_search_test.c $(CFLAGS)

test_hasht: hasht_test.o prime.o
	clang -o test_hasht hasht_test.o prime.o $(CFLAGS1)
hasht_test.o: hasht_test.c
	clang -c hasht_test.c $(CFLAGS)

prime: prime.o
	clang -o prime prime.o $(CFLAGS1)
prime.o: prime.c
	clang -c prime.c $(CFLAGS)





clean:
	rm test_rbt test_bst tale_freq seq_search test_hasht *.o
