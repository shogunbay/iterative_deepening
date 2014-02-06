#ifndef graph_h
#define graph_h

#define MAX_BUFFER_SIZE 	32

/* ---------- graph structure definitions ---------- */
typedef struct vertex_t {
	int state;
	int visited;
	char name[MAX_BUFFER_SIZE];
	struct edge_t *edges;
	struct vertex_t *next_vertex;
} Vertex;
        
typedef struct edge_t {
	int cost;
	struct vertex_t *connection;
	struct edge_t *next_edge;
} Edge;

typedef struct graph_t {
	struct vertex_t *vertices;
} Graph;

/* ---- info extraction structure definitions ---- */
typedef struct connections {
	int from_state;
	int to_state;
	int cost;
	int from_edge;
	struct connections *next;
} Connections;

typedef struct state_pos_t {
	int state;
	int file_pos;
	char name[MAX_BUFFER_SIZE];
} PositionState;

typedef struct result_t {
	int state;
	int cost;
	struct result_t *next;
	struct result_t *prev;
} Result;

/* ------------ function prototypes ------------ */
char *load_file(char *, int *);
int get_start(char *pfile);
int get_target(char *pfile);

PositionState create_state(char *, int);
int create_edges(char *pfile, Graph *graph, Vertex *entry_vertex, PositionState pos_state, Connections **connections);
Connections *create_connections();

Graph *new_graph(void);
Vertex *add_vertex(Graph *graph, Vertex *entry_point, int state, char *name, unsigned long int vertex_addresses[]);
Edge *add_edge(Graph *graph, Vertex *entry_vertex, int state, int connection, int cost);
void connect_graph(Graph *graph, Connections *connections, unsigned long int *vertex_connections);

Graph *build_graph(char *, int, unsigned long int *);
int iterative_deepening(Vertex *vertex, int target, int level, Result **result, int found);

Result *new_result();
void result_add(Result **result, int state, int cost);

#endif
