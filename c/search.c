#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/*--------------------- search algorithm ---------------------*/

int iterative_deepening(Vertex *vertex, int target, int level, Result **result, int found) {

	if(vertex->state == target) {
		result_add(result, vertex->state, 0);
		return(1);
	}

	if(vertex->visited)
		return(0);

	if(!level) {
		vertex->visited = 0;
		return(0);
	}

	Edge *edge = vertex->edges;
	vertex->visited = 1;

	while(edge->next_edge != NULL && !found) {
		edge = edge->next_edge;
		found = iterative_deepening(edge->connection, target, level - 1, result, 0);
	}

	if(found)
		result_add(result, vertex->state, edge->cost);

	vertex->visited = 0;
	return(found);
}

