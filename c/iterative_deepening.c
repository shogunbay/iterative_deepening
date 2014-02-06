#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

/* ------------------ main file ------------------ */

#define CHEAT_OFF 1
#define CHEAT_ON 500

#define SEARCH_INIT_LEVEL  CHEAT_OFF


int main(int argc, char *argv[]) {

	/* hi */
	double secs;
	clock_t ticks;
	unsigned long int *vertex_addresses; 
	int start, target, file_size, file_pos, level, sum, found = 0;
	char *file_buffer, file[] = "Graphs/graph4.txt";
	Graph *graph;
	Result *result, *rhead; 

	/* yeah, dangerous, since never re-allocated - fuck that and save time :~D */
	vertex_addresses = (unsigned long int *)malloc(2500000 * sizeof(unsigned long int));

	result = new_result();
	rhead = result;

	/* run clock */
	ticks = clock();

		/* input */
		switch(argc) {
			case 2:
				file_buffer = load_file(argv[1], &file_size);
				break;
			case 1:
				file_buffer = load_file(file, &file_size);
				break;
			default:
				printf("\nFehlerhafte Eingabe\n\n");
				exit(1);
		}

		/* organize */
		start = get_start(file_buffer);
		target = get_target(file_buffer);
		graph = build_graph(file_buffer, file_size, vertex_addresses);

		/* search */
		for(level = SEARCH_INIT_LEVEL, found = 0; found != 1 && level < 1000; level++)
			found = iterative_deepening(graph->vertices->next_vertex, target, level, &result, 0);

		/* format + output */
		for(sum = 0; rhead->next; rhead = rhead->next)
			sum += rhead->next->cost;

		if(sum) {
			printf("\n%d\n", sum);

			while(result->prev && result->prev->state) {
				if(result->prev->state != result->state)
				printf("Z%d ", result->state);
				result = result->prev;
			}
			printf("Z%d\n\n", result->state);
		} else
			printf("\nZiel nicht erreichbar\n\n");
	
	/* stop clock */
	ticks = clock() - ticks;
	secs = ((double)ticks) / CLOCKS_PER_SEC;
	printf("\n\n(Duration %.3lf seconds)\n", secs);

	/* bye */
	free(vertex_addresses); 
	free(file_buffer); 
	return(0); 
}
