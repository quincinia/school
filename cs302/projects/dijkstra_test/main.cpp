#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//change depending on # of vertices
const int V = 9;

//returns the smallest tentative distance from the vertices that haven't been visited
int minDistance(int dist[], bool sptSet[], int size) {
	int min = INT_MAX;
	int min_index;

	for (int v = 0; v < size; ++v)
		if (sptSet[v] == false && dist[v] <= min)
		{
			min = dist[v];
			min_index = v;
		}

	return min_index;
}

void dijkstra(int graph[V][V], int src)
{
	//distances to every vertex from src
	int dist[V];

	//true if that vertex is "visited"/within included in the shortest path set
	bool visited[V];

	//describes the edges of the path(s)
	int parent[V];

	//initialize distances
	for (int i = 0; i < V; ++i)
	{
		dist[i] = INT_MAX;
		visited[i] = false;
	}

	//source is always 0
	dist[src] = 0;
	parent[src] = -1;

	for (int count = 0; count < V-1; ++count)
	{
		//index of min distance vertex
		//on the first iteration this will always be the source
		int u = minDistance(dist, visited, V);

		//mark min vertex as visited
		visited[u] = true;

		for (int v = 0; v < V; v++)
			if (!visited[v] && //not visited
				graph[u][v] && //edge exists
				graph[u][v] != INT_MAX && //only check neighbors
				dist[u] != INT_MAX && //make sure its connected to the current set (this can be moved outside the loop)
				dist[u]+graph[u][v] < dist[v]) //distance is better than current
			{
				parent[v] = u;
				dist[v] = dist[u]+graph[u][v];
			}

	}

	//print solution
	std::cout << "Vertex Distance from Source\n";
	for (int i = 0; i < V; i++)
		std::cout << i << " tt " << dist[i] << std::endl;

	//print edges
	cout << "Edge \tWeight" << endl;
	for (int i = 0; i < V; ++i)
		if (i != src)
			cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
}

void solveFile();

int main()
{
	int graph[V][V] = {
		{0, 4, 0, 0, 0, 0, 0, 8, 0},
		{4, 0, 8, 0, 0, 0, 0, 11, 0},
		{0, 8, 0, 7, 0, 4, 0, 0, 2},
		{0, 0, 7, 0, 9, 14, 0, 0, 0},
		{0, 0, 0, 9, 0, 10, 0, 0, 0},
		{0, 0, 4, 14, 10, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 2, 0, 1, 6},
		{8, 11, 0, 0, 0, 0, 1, 0, 7},
		{0, 0, 2, 0, 0, 0, 6, 7, 0}
	};

	dijkstra(graph, 0);

	//solveFile();
	return 0;
}

void solveFile()
{
	ifstream input;
	input.open("input.txt");

	string info;
	getline(input, info);

	stringstream parser(info);

	//initialize matrix
	int vertices;
	parser >> vertices;
	int graph[vertices][vertices];

	//set default edge weights
	for (int i = 0; i < vertices; ++i)
		for (int j = 0; j < vertices; ++j)
		{
			graph[i][j] = INT_MAX;
			if (i == j)
				graph[i][j] = 0;
		}

	//fill in values for each vertex
	parser.clear();
	while (getline(input, info))
	{
		int vertex, neighbor, weight;
		parser.str(info);
		parser >> vertex;
		while (parser.good())
		{
			parser >> neighbor;
			parser >> weight;
			graph[vertex-1][neighbor-1] = weight;
		}
		parser.clear();
	}

	//just copypasting the code bc im not tryna work with multidim arrays
	int src = 0;


	int dist[vertices];
	bool visited[vertices];
	int parent[vertices];

	for (int i = 0; i < vertices; ++i)
	{
		dist[i] = INT_MAX;
		visited[i] = false;
	}

	dist[src] = 0;
	parent[src] = -1;

	for (int count = 0; count < vertices-1; ++count)
	{
		int u = minDistance(dist, visited, vertices);
		visited[u] = true;

		for (int v = 0; v < vertices; v++)
			if (!visited[v] && //not visited
				graph[u][v] && //edge exists
				graph[u][v] != INT_MAX && //only check neighbors
				dist[u] != INT_MAX && //make sure its connected to the current set (this can be moved outside the loop)
				dist[u]+graph[u][v] < dist[v]) //distance is better than current
			{
				parent[v] = u;
				dist[v] = dist[u]+graph[u][v];
			}

	}

	//print solution
	std::cout << "Vertex Distance from Source\n";
	for (int i = 0; i < vertices; i++)
		std::cout << i << " tt " << dist[i] << std::endl;

	//print edges
	cout << "Edge \tWeight" << endl;
	for (int i = 0; i < vertices; ++i)
		if (i != src)
			cout << parent[i] << " -> " << i << "\t" << graph[parent[i]][i] << endl;
}


