
iterative_deepening.c.run: iterative_deepening.o graph.o loader.o extractor.o search.o
	gcc -g -O0 -o iterative_deepening.c.run iterative_deepening.o graph.o loader.o extractor.o search.o && make clean

search.o: search.c
	gcc -g -O0 -c search.c

extractor.o: extractor.c
	gcc -g -O0 -c extractor.c

loader.o: loader.c
	gcc -g -O0 -c loader.c

iterative_deepening.o: iterative_deepening.c
	gcc -g -O0 -c iterative_deepening.c

graph.o: graph.c
	gcc -g -O0 -c graph.c

clean:
	$(RM) iterative_deepening.o graph.o loader.o extractor.o search.o \[C-ompiler\]
