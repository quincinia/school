#include <iostream>
#include <climits>

using namespace std;

//change as needed
const int V = 6;

//find index of "closest" vertex to the current MST
//will only pick from the unvisited vertices
int findMin(int dist[], bool visited[])
{
	int min = INT_MAX, min_index;
	for (int i = 0; i < V; ++i)
		if (!visited[i] && dist[i] < min)
		{
			min = dist[i];
			min_index = i;
		}
	return min_index;
}

//print the edges of the new MST
void printMST(int parent[], int graph[][V], int src)
{
	cout << "Edge \tWeight" << endl;
	for (int i = 0; i < V; ++i)
		if (i != src)
			cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
}

void prims(int graph[][V], int src)
{
	//distances from src to each vertex
	int dist[V];

	//stores visited vertices
	bool visited[V];

	//describes the edges of the MST
	int parent[V];

	for (int i = 0; i < V; ++i)
	{
		dist[i] = INT_MAX;
		visited[i] = false;
	}

	dist[src] = 0;
	parent[src] = -1; //starting vertex has no parent

	//maybe see dijkstras algo for updated logic
	for (int count = 0; count < V-1; ++count)
	{
		//find "closest" unvisited vertex
		int u = findMin(dist, visited);

		//mark it as visited
		visited[u] = true;

		//update distances of the neighbors of the
		//picked vertex
		for (int v = 0; v < V; ++v)
			if (graph[u][v] && //edge exists
				!visited[v] && //only pick unvisited
				graph[u][v] < dist[v]) //new distance is shorter
			{
				parent[v] = u;
				dist[v] = graph[u][v];
			}
	}
	printMST(parent, graph, src);
}

int main()
{
	/*
	int graph[V][V] = {
		{ 0, 2, 0, 6, 0 },
		{ 2, 0, 3, 8, 5 },
		{ 0, 3, 0, 0, 7 },
		{ 6, 8, 0, 0, 9 },
		{ 0, 5, 7, 9, 0 }
	};
	*/
	int graph[V][V] = {
		{0, 10, 20, INT_MAX, INT_MAX, INT_MAX},
		{10, 0, INT_MAX, 50, 10, INT_MAX},
		{20, INT_MAX, 0, 20, 33, INT_MAX},
		{INT_MAX, 50, 20, 0, 20, 2},
		{INT_MAX, 10, 33, 20, 0, 1},
		{INT_MAX, INT_MAX, INT_MAX, 2, 1, 0}
	};
	prims(graph, 0);
	return 0;
}
