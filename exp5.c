#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a connected, directed and weighted graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// A utility function to find set of an element i
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// A utility function to do union of two sets of x and y
void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    if (xset != yset)
        parent[xset] = yset;
}

// Function to compare two edges according to their weights
int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// Function to implement Kruskal's algorithm
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    int E = graph->E;

    // Allocate memory for creating MST
    struct Edge result[V]; // Tnis will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight.
    qsort(graph->edge, E, sizeof(graph->edge[0]), compare);

    // Allocate memory for creating parent[]
    int parent[V];
    for (int i = 0; i < V; ++i)
        parent[i] = -1;

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < E) {
        // Step 2: Pick the smallest edge and increment the index
        struct Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        // If including this edge does't cause cycle, include it in result[]
        // and increment the index of result[]
        if (x != y) {
            result[e++] = next_edge;
            unionSet(parent, x, y);
        }
        // Else discard the next_edge
    }

    // print the contents of result[] to display the built MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    return;
}

// Function to implement Prim's algorithm
void PrimMST(struct Graph* graph) {
    int V = graph->V;
    int E = graph->E;

    // The output array.  dist[i] will hold the shortest distance from src to i
    int parent[V];
    int key[V];
    int mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Always include first vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = -1;
        for (int v = 0; v < V; v++)
            if (mstSet[v] == 0 && (u == -1 || key[v] < key[u]))
                u = v;

        // Add the picked vertex to the MST Set
        mstSet[u] = 1;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        for (int v = 0; v < E; v++)
            if (graph->edge[v].src == u || graph->edge[v].dest == u)
                if (mstSet[graph->edge[v].dest] == 0 && graph->edge[v].weight < key[graph->edge[v].dest]) {
                    parent[graph->edge[v].dest] = u;
                    key[graph->edge[v].dest] = graph->edge[v].weight;
                }
    }

    // print the constructed MST
    printf("Following are the edges in the constructed MST\n");
    for (int i = 1; i < V; i++)
        printf("%d -- %d == %d \n", parent[i], i, key[i]);
}

int main() {
    int V = 6; // Number of vertices in graph
    int E = 8; // Number of edges in graph
    struct Graph* graph = createGraph(V, E);

    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 4;

    // add edge 0-2
    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 9;

    // add edge 0-3
    graph->edge[2].src = 2;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 4;

    // add edge 1-3
    graph->edge[3].src = 3;
    graph->edge[3].dest = 4;
    graph->edge[3].weight = 8;

    // add edge 2-3
    graph->edge[4].src = 4;
    graph->edge[4].dest = 0;
    graph->edge[4].weight = 3;
    graph->edge[5].src = 3;
    graph->edge[5].dest = 5;
    graph->edge[5].weight = 2;
    graph->edge[6].src = 2;
    graph->edge[6].dest = 5;
    graph->edge[6].weight = 6;
    graph->edge[7].src = 0;
    graph->edge[7].dest = 5;
    graph->edge[7].weight = 2;
    
    
    

    printf("Kruskal's Minimum Spanning Tree:\n");
    KruskalMST(graph);

    printf("\nPrim's Minimum Spanning Tree:\n");
    PrimMST(graph);

    return 0;
}
