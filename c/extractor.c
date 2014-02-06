#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/*--------------- information extraction ---------------*/

int get_start(char *pfile) {

	char start[255];

	while( !(pfile[0] == 't' && pfile [2] == 'Z') && pfile[2] != 0)
		pfile++;

	if( *(pfile + 2) == 0 ) {
		printf("\nFehlerhafte Eingabe\n\n");
		exit(1);
	}

	/* jump to the x in "Start Zx" */
	pfile += 3;

	int i;
	for(i = 0; *pfile != '\n'; i++, pfile++)
		start[i] = *pfile;

	start[i] = 0;
	return(atoi(start));
}

int get_target(char *pfile) {

	char target[255];

	while( !(pfile[0] == 'l' && pfile[2] == 'Z') && pfile[2] != 0 )
		pfile++;

	if( *(pfile + 2) == 0 ) {
		printf("\nFehlerhafte Eingabe\n\n");
		exit(1);
	}

	/* jump to the x in "Ziel Zx" */
	pfile += 3;

	int i;
	for(i = 0; *pfile != '\n'; i++, pfile++)
		target[i] = *pfile;

	target[i] = 0;
	return(atoi(target));
}

Graph *build_graph(char *pfile, int file_size, unsigned long int vertex_addresses[]) {

	unsigned long file_pos;
	PositionState pos_state;

	Graph *graph = new_graph();
	Vertex *entry_vertex = graph->vertices;
	Connections *connections = create_connections();
	Connections *connections_first = connections;

	file_pos = 0;

	while(pos_state.file_pos < file_size && pos_state.file_pos != -1 ) {
		pos_state = create_state(pfile, file_pos);

		/* eof? => exit function */
		if(pos_state.file_pos == -1)
			break;

		entry_vertex = add_vertex(graph, entry_vertex, pos_state.state, pos_state.name, vertex_addresses);
		
		file_pos = create_edges(pfile, graph, entry_vertex, pos_state, &connections);
	}

	while(connections_first->next) {
		connections_first = connections_first->next;
		connect_graph(graph, connections_first, vertex_addresses);
	}

	return(graph);
}

PositionState create_state(char *pfile, int file_pos) {

	int pos;
	PositionState position_state;
	char state[MAX_BUFFER_SIZE];

	pfile += file_pos;
	pos = 0;

	/* 'i' != pfile[2] to avoid finding "Ziel" instead of "Zx" */
	while( !(('\n' == pfile[0]) && ('Z' == pfile[1]) && ('i' != pfile[2])) && pfile[2] != 0) {
		pfile++;
		file_pos++;
	}

	if(pfile[2] == 0) {
		position_state.file_pos = -1;
		return(position_state);
	}

	/* jump to the state number, e.g. 1 in "Z1" */
	pfile += 2;
	file_pos += 2;

	while(*pfile != ':') {
		state[pos++] = *pfile++;
		file_pos++;
	}
	state[pos] = 0;

	position_state.state = atoi(state);

	/* jump to the name */
	pfile += 2;
	file_pos += 2;
	pos = 0;

	while(*pfile != '\n') {
		position_state.name[pos++] = *pfile++;
		file_pos++;
	}
	position_state.name[pos] = 0;

	position_state.file_pos = file_pos;
	return(position_state);
}

int create_edges(char *pfile, Graph *graph, Vertex *entry_vertex, PositionState pos_state, Connections **connections) {

	int current_edge = 0;
	int pos = 0;
	char state[255];
	char edge_nr[255];
	char edge_content[255];
	char cost[255];
	char name[255];

	pfile += pos_state.file_pos;
	
	/* get all edges for a state */
	while( !(pfile[0] == '\n' && pfile[1] != 'K') && pfile[1] != 0) {

		if(pfile[1] == 0) 
			return(-1);

		/* jump to the edge number, e.g. 3 in "K3" */
		pfile += 2;
		pos_state.file_pos += 2;
		pos = 0;

		while(*pfile != ':') {
			edge_nr[pos++] = *pfile++;
			pos_state.file_pos++;
		}

		edge_nr[pos] = 0;
		current_edge++;

		/* jump to the target-state number, e.g. 2 in "Z23," */
		pfile += 3;
		pos_state.file_pos += 3;
		pos = 0;

		while(*pfile != ',') {
			edge_content[pos++] = *pfile++;
			pos_state.file_pos++;
		}
		edge_content[pos] = 0;

		/* jump to the cost */
		pfile += 2;
		pos_state.file_pos += 2;
		pos = 0;

		while(*pfile != '\n') {
			cost[pos++] = *pfile++;
			pos_state.file_pos++;
		}
		cost[pos] = 0;

		add_edge(graph, entry_vertex, pos_state.state, atoi(edge_content), atoi(cost));

		/* save connections to apply them after all nodes nodes have been created */
		(*connections)->next = create_connections();
		(*connections)->next->from_state = pos_state.state;
		(*connections)->next->to_state = atoi(edge_content);
		(*connections)->next->cost = atoi(cost);
		(*connections)->next->from_edge = current_edge;
		(*connections) = (*connections)->next;
	}

	return(pos_state.file_pos);
}
