#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*------------------ graph results ------------------*/

Result *new_result() {
	Result *result = (Result *)malloc(sizeof(Result));
	result->cost = 0;
	result->state = 0;
	result->next = NULL;
	return(result);
}

void result_add(Result **result, int state, int cost) {
	(*result)->next = new_result();
	(*result)->next->state = state;
	(*result)->next->cost = cost;
	(*result)->next->next = NULL;
	(*result)->next->prev = *result;
	*result = (*result)->next;
}

/*------------------ graph operations ------------------*/

Connections *create_connections() {
	Connections *cons = (Connections *)malloc(sizeof(Connections));
	cons->next = NULL;

	return(cons);
}

/* this subfunction is only used locally within this file */
Edge *new_edge() {
	Edge *edge = (Edge *)malloc(sizeof(Edge));

	edge->connection = NULL;
	edge->next_edge = NULL;

	return(edge);
}

Graph *new_graph() {
	Graph *graph;

	graph = (Graph *)malloc(sizeof(Graph)); 
	graph->vertices = (Vertex *)malloc(sizeof(Vertex));

	graph->vertices->visited = 0;
	graph->vertices->state = 0;
	graph->vertices->next_vertex = NULL;
	graph->vertices->edges = new_edge();

	return(graph);
}

void connect_graph(Graph *graph, Connections *connections, unsigned long int vertex_addresses[]) {

	int edge;
	Vertex *pvertex; 
	Vertex *pconnection; 
	Edge *pedge, *psave;

	pvertex = (Vertex *)vertex_addresses[connections->from_state];
	pconnection = (Vertex *)vertex_addresses[connections->to_state];

	/* find the right edge */
	pedge = pvertex->edges;
	for(edge = 0; edge < connections->from_edge; edge++)
		pedge = pedge->next_edge;

	if(pedge == NULL) {
		printf("\nFehlerhafte Eingabe\n\n");
		exit(1);
	}

	/* avoid redundant reconnecting */
	if(pedge->connection != pconnection)
		pedge->connection = pconnection;
}

Vertex *add_vertex(Graph *graph, Vertex *entry_point, int state, char *name, unsigned long int vertex_addresses[]) {

	Vertex *pvertex = entry_point;

	while(pvertex->next_vertex != NULL) 
		pvertex = pvertex->next_vertex;

	pvertex->next_vertex = (Vertex *)malloc(sizeof(Vertex));
	pvertex->next_vertex->state = state;
	pvertex->next_vertex->visited = 0;
	memcpy(pvertex->next_vertex->name, name, MAX_BUFFER_SIZE);
	pvertex->next_vertex->next_vertex = NULL;
	pvertex->next_vertex->edges = new_edge();

	vertex_addresses[pvertex->next_vertex->state] = (unsigned long int)pvertex->next_vertex;
		
	return(pvertex->next_vertex);
};

Edge *add_edge(Graph *graph, Vertex *entry_vertex, int state, int connection, int cost) {

	Vertex *pconnection; 
	Edge *pedge;

	/* find vertex in state */
	pedge = entry_vertex->edges;
	while(pedge->next_edge != NULL && pedge->next_edge->connection != pconnection) 
		pedge = pedge->next_edge;

	pedge->next_edge = new_edge();
	pedge->next_edge->cost = cost;
	pedge->next_edge->connection = NULL;

	return(pedge->next_edge);
};
