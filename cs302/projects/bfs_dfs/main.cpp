#include <iostream>
#include <stack>
#include <queue>

using namespace std;

const int V = 9;

//this adjacency matrix will have 0's across the diagonal

//recursive DFS
void dfsRec(bool graph[][V], int curr, bool visited[])
{
	visited[curr] = true;
	cout << curr << " ";

	//recurse on all unvisited neighbors
	for (int i = 0; i < V; ++i)
		if (!visited[i] && graph[curr][i])
		{
			//if spanning tree, mark this edge
			dfsRec(graph, i, visited);
		}
}

//iterative DFS
void dfsItr(bool graph[][V], int src)
{
	//DFS will travel from the most recently visited vertex, so a stack will be used
	stack<int> s;
	bool visited[V];
	for (int i = 0; i < V; ++i)
		visited[i] = false;

	s.push(src);
	visited[src] = true;
	cout << src << " ";

	while (!s.empty())
	{
		//if there are no more unvisited neighbors, then we need to backtrack
		bool unvisited = false;
		int unvisited_vertex; //holds 1 of the unvisited neighbors
		for (int i = V-1; i >= 0; --i)
			if (graph[s.top()][i] && !visited[i])
			{
				unvisited = true;
				unvisited_vertex = i;
			}

		if (unvisited == false)
			s.pop();
		else
		{
			s.push(unvisited_vertex);
			visited[unvisited_vertex] = true;
			cout << unvisited_vertex << " ";
			//if spanning tree, mark this edge
		}
	}
}

//the recursive and iterative versions of BFS are pretty much the same
//https://www.techiedelight.com/breadth-first-search/
//this will only use the iterative version
void bfs(bool graph[][V], int src)
{
	queue<int> q;
	bool visited[V];
	for (int i = 0; i < V; ++i)
		visited[i] = false;

	q.push(src);
	visited[src] = true;
	cout << src << " ";

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		//visit all unvisited neighbors and add them to the queue
		for (int i = 0; i < V; ++i)
			if (graph[curr][i] && !visited[i])
			{
				visited[i] = true;
				cout << i << " ";
				//if spanning tree, mark this edge
				q.push(i);
			}
	}
}
int main()
{
	//same graph as from slides
	//https://www.autonomousrobotslab.com/uploads/5/8/4/4/58449511/cs302-131-graphs-introduction.pdf
	bool graph[][V] = {
		{0, 1, 0, 0, 0, 1, 0, 0, 1}, //a
		{1, 0, 1, 0, 1, 0, 0, 0, 0}, //b
		{0, 1, 0, 1, 1, 0, 0, 0, 0}, //c
		{0, 0, 1, 0, 0, 0, 1, 1, 0}, //d
		{0, 1, 1, 0, 0, 0, 1, 0, 0}, //e
		{1, 0, 0, 0, 0, 0, 1, 0, 0}, //f
		{0, 0, 0, 1, 1, 1, 0, 0, 0}, //g
		{0, 0, 0, 1, 0, 0, 0, 0, 0}, //h
		{1, 0, 0, 0, 0, 0, 0, 0, 0}  //i
	};

	bool visited[V];
	for (int i = 0; i < V; ++i)
		visited[i] = false;

	cout << "DFS rec: ";
	dfsRec(graph, 0, visited);
	cout << endl;


	cout << "DFS itr: ";
	dfsItr(graph, 0);
	cout << endl;

	cout << "BFS itr: ";
	bfs(graph, 0);
	cout << endl;
	return 0;
}
