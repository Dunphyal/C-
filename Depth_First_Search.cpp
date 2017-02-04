// Alex Dunphy, Student Number: 12303659
// Assignment 4


#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_NODE_CONNECTIONS 16
#define MAX_NODES 64

// declaration of the variables and arrays contained in each node
typedef struct Graph_Node {
	char data;
	int number_of_edges;
	
	// weights of each edge
	int weights[MAX_NODE_CONNECTIONS];
	int connected_R[MAX_NODE_CONNECTIONS];           // array of connected nodes to the right
	int connected_L[MAX_NODE_CONNECTIONS];           // array of connected nodes to the left

	bool visited; //used for DFS to prevent infinite loop
	int counter_R, counter_L;
	int position;
	int prev;
	

} Graph_Node;

typedef struct Graph {
	// adjacency lists are stored inside nodes in my graph.
	Graph_Node vertices[MAX_NODES];

	int number_of_vertices;
} Graph;

//Function used to add new vertex to the graph.
// Sets initial values for the variables of each node within vertices and adds the data passed to the function
int add_vertex_to_graph(Graph* graph, char data) {
	assert(graph != NULL);
	assert(graph->number_of_vertices < MAX_NODES);

	int index = graph->number_of_vertices;
	graph->vertices[index].data = data;          // sets the data of the node at index
	graph->vertices[index].number_of_edges = 0;
	graph->vertices[index].visited = false;      // flag intially set to false
	graph->vertices[index].counter_R = 0;
	graph->vertices[index].counter_L = 0;
	graph->vertices[index].position = 0;
	graph->vertices[index].prev = 0;

	graph->number_of_vertices++;                 //increment number of vertices by one
	return index;
}

// start_vertex_index  =  left node
// end_vertex_index  = right node
// The function is used to add an edge in both directions, assert statements are used to check
// for scenarios we dont want eg. empty graph
// Two arrays are used to store the edges for each node, connected_L and connected_R
// the arrrays are updated by firstly finding the next available space in the array, counter_R/L
// The node to be addded to array is added in the position counter_R/L
// the value of counter_R/L is incremented to prevent data being overwritten
// Two arrays are used for connected nodes as only having one ,although possible, 
// can result in an infinte loop between nodes with only one connected node or a crash eg. node: E

void add_edge_undirected(Graph* graph, int start_vertex_index,
	int end_vertex_index, int weight) {
	assert(graph != NULL);                                       // abort if graph is empty
	assert(start_vertex_index > -1 &&
		start_vertex_index < graph->number_of_vertices);         // abort if start_vertex_index is less negative and less than no. vertices
	assert(end_vertex_index > -1 &&
		end_vertex_index < graph->number_of_vertices);

	// for each node the other node is added to one its two connected arrays, this is done
	// so that both nodes can travel to the other ie. the graph is undirected
	// adds right node to left nodes connected_R array
	int temp = graph->vertices[start_vertex_index].counter_R;   // adding end_vertex_index to array of connected nodes of start_vertex_index
	graph->vertices[start_vertex_index].connected_R[temp] =
		end_vertex_index;   
	int left_vert_edge_count = graph->vertices[start_vertex_index].number_of_edges;
	graph->vertices[start_vertex_index].weights[left_vert_edge_count] = weight; // weight between nodes added
	graph->vertices[start_vertex_index].number_of_edges++;
	graph->vertices[start_vertex_index].counter_R++; 

	// adds left node to right nodes connected_L array
	int temp_2 = graph->vertices[end_vertex_index].counter_L;   // adding end_vertex_index to array of connected nodes of start_vertex_index
	graph->vertices[end_vertex_index].connected_L[temp_2] =
		start_vertex_index;
	int right_vert_edge_count = graph->vertices[end_vertex_index].number_of_edges;
	graph->vertices[end_vertex_index].weights[right_vert_edge_count] = weight; // weight between nodes added
	graph->vertices[end_vertex_index].number_of_edges++;
	graph->vertices[end_vertex_index].counter_L++;


}

// This function is used to check if every node in the graph has been visited ie. graph has been
// fully searched without finding the target node
bool finished(Graph*graph) {
	int graph_end = graph->number_of_vertices;

	int check = 0;
	for (int i = 0; i < graph_end; i++) { // cycles through every node in the graph

		if (graph->vertices[i].visited == true) { // if all connected nodes have been visited
			check++;
		}
	}

	if (check == graph_end) { // if every node has been visited return true
		return true;
	}
	else
		return false;
}

// The DFS function is a bool function which on each iteration initially prints out the value 
// of the current node (start), the program then sets the visited flag of the current node to true which
// will be used to determine the nodes to be visited next. The function first checks wether the value in
// the current node is equal to the value of the target node, if so the function returns true. Otherwise
// the function check wether all nodes have been visited
// This is done by calling the finished function. If this funciton returns true the entire list has been
// searched meaning the target doesnt exist within the graph.
// If neither of these are checks are satisified, the function will look for the next node to check
// by searching the array of connected nodes of the current node (connectd_R) for a unvisited node if 
// one exist the function will recurse using the unvisited node as start, if none exist within
// the connected_R array the function will check for a node in the connected_L array. The function will
// first check connected_L for a unvisited node if none exist the function will recurse using the first
// element in connected_L as start.

bool dfs(Graph* graph, int start, int target) {

	char current = graph->vertices[start].data;
	char goal = graph->vertices[target].data;

	printf("%c ", current);                              // print out data in start node for each recursion

	graph->vertices[start].visited = true;               // set visited flag to true

	if (current == goal) {                               // check if taget found
		return true;
	}
	
	else if (finished(graph) == true) {                  // check is entire graph visited
		return false;
	}

	int end = graph->vertices[start].counter_R;
	for (int i = 0; i < end; i++) {                 // cycle through connected nodes up to last added element
		int temp = graph->vertices[start].connected_R[i];
		if (graph->vertices[temp].visited == false) { // check if connected nodes have been visited

			bool halt = false;
			halt = dfs(graph, temp, target);        // recurse using unvisited node, ie. move to unvisted node
			if (halt == true) {
				return true;                        // catch recursion
			}
			else if (halt == false) {
				return false;                       // catch recursion
			}
		}
	}

	int stop = graph->vertices[start].counter_L;
	for (int i = 0; i < stop;i++) {                 // cycle through connected_L array up to last added element
		int choice = graph->vertices[start].connected_L[i];
		if (graph->vertices[choice].visited == false) {   // first look for unvisited node
			bool halt = dfs(graph, choice, target);       // recurse using unvisited node as start 
			if (halt == true) {                             
				return true;
			}
			else if (halt == false) {
				return false;
			}
		}
	}
	// if no unvisited node exist recurse using first element in connected_L
	int choice = graph->vertices[start].connected_L[0];
	bool halt = dfs(graph, choice, target);         
	if (halt == true) {                             
		return true;
	}
	else if (halt == false) {
		return false;
	}
}


// the reset function is used to reset the visited flag for each node, this is done by cycling
// through the nodes using a for loop and at each iteration setting the corresponding visited to false
void reset(Graph* graph) {
	for (int i = 0; i < graph->number_of_vertices; i++) {

		graph->vertices[i].visited = false;
	}
}

//The set up function for the Depth first search function (dfs) is used in order to
//print out the intial line, call the reset for the next time the nodes are used and finally
//to output wether the target was found or not
bool dfs_set_up(Graph* graph, int start, int target) {

	char begin = graph->vertices[start].data;
	printf("DFS from %c :", begin);
	bool answer = dfs(graph, start, target);
	reset(graph);
	if (answer == true) {
		printf("  target found - HALT \n");
		return true;
	}

	else if (answer == false) {
		printf("  target not found - HALT \n");
		return false;
	}
}


int main() {
	Graph my_graph;
	my_graph.number_of_vertices = 0;

	// look-up table to get index of each graph letter in my array
	// this assumes each letter is only ever entered once
	int letter_indices[100000];
	memset(&letter_indices, -1, sizeof(int) * 100000);

	for (int i = 'A'; i <= 'L'; i++) {
		letter_indices[i] = add_vertex_to_graph(&my_graph, (char)i);
	}
	add_edge_undirected(&my_graph, letter_indices['A'], letter_indices['B'], 1);
	add_edge_undirected(&my_graph, letter_indices['B'], letter_indices['C'], 2);
	add_edge_undirected(&my_graph, letter_indices['B'], letter_indices['D'], 2);
	add_edge_undirected(&my_graph, letter_indices['C'], letter_indices['E'], 3);
	add_edge_undirected(&my_graph, letter_indices['C'], letter_indices['F'], 2);
	add_edge_undirected(&my_graph, letter_indices['D'], letter_indices['G'], 2);
	add_edge_undirected(&my_graph, letter_indices['F'], letter_indices['H'], 1);
	add_edge_undirected(&my_graph, letter_indices['F'], letter_indices['I'], 2);
	add_edge_undirected(&my_graph, letter_indices['F'], letter_indices['J'], 4);
	add_edge_undirected(&my_graph, letter_indices['G'], letter_indices['J'], 1);
	add_edge_undirected(&my_graph, letter_indices['G'], letter_indices['L'], 3);
	add_edge_undirected(&my_graph, letter_indices['G'], letter_indices['K'], 2);
	add_edge_undirected(&my_graph, letter_indices['I'], letter_indices['K'], 11);
	add_edge_undirected(&my_graph, letter_indices['J'], letter_indices['L'], 5);


	bool answer = dfs_set_up(&my_graph, letter_indices['A'], letter_indices['X']);
	bool answer_2 = dfs_set_up(&my_graph, letter_indices['K'], letter_indices['B']);

	return 0;
}