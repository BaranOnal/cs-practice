//https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
//Priorty queue versiyonu da linkte var.


#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 5


int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;
    
    for (int i = 0; i < V; i++) {
        if (mstSet[i] == false && key[i] < min)
            min = key[i], min_index = i;
    }
    return min_index;
}
int printMST(int parent[], int graph[V][V])
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i,
            graph[parent[i]][i]);
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < V - 1; i++) {
        
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for (int j = 0; j < V; j++) 
            if (graph[u][j] && !mstSet[j] && graph[u][j] < key[j])
                parent[j] = u, key[j] = graph[u][j];
        
    }
    printMST(parent, graph);
}

int main()
{
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };

    primMST(graph);

    return 0;
}