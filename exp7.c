#include <stdio.h>

#define INF 99999

struct Edge {
    int src, dest, weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int src)
{
    int dist[V];
    int i, j;

    for (i = 0; i < V; i++)
        dist[i] = INF;

    dist[src] = 0;

    for (i = 1; i <= V - 1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (j = 0; j < E; j++)
    {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            printf("Negative weight cycle exists\n");
            return;
        }
    }

    printf("Vertex Distance\n");

    for (i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}

int main()
{
    int V, E, i, src;

    scanf("%d %d", &V, &E);

    struct Edge edges[E];

    for (i = 0; i < E; i++)
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);

    scanf("%d", &src);

    bellmanFord(edges, V, E, src);

    return 0;
}
