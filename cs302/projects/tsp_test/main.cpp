#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
#include <algorithm> //next_permutation

using namespace std;

//change as needed
const int V = 5;

float solution(float graph[][V], int start)
{
	vector<int> vertex; //used to create the permutations?

	int path[V]; //tsp route (excluding start?)
	int temp[V];

	//add all other vertices to vector
	for (int i = 0; i < V; ++i)
		if (i != start) vertex.push_back(i);

	float min_path = INT_MAX;
	do {
		float current_pathweight = 0;
		int k = start;

		//generate weight for path (if it exists)
		bool invalid_path = false;
		for (int i = 0; i < vertex.size(); ++i)
		{
			//check if path exists
			//graph should use INT_MAX to represent no connection
			if (graph[k][vertex[i]] == INT_MAX)
			{
				invalid_path = true;
				break;
			}

			//if the path exists, continue calculating the weight
			current_pathweight += graph[k][vertex[i]];
			k = vertex[i];
			temp[i] = k;
		}
		if (graph[k][start] == INT_MAX)
			invalid_path = true;

		//go to next permutation if path does not exist
		if (invalid_path) continue;

		current_pathweight += graph[k][start];
		//update min path
		min_path = min(min_path, current_pathweight);
		if (min_path == current_pathweight)
			for (int i = 0; i < V-1; i++)
				path[i] = temp[i];
	} while (next_permutation(vertex.begin(), vertex.end()));

	cout << start+1 << " to ";
	for (int i = 0; i < V-1; ++i)
	{
		if (i == V-2)
			cout << path[i]+1 << " to " << start+1 << endl;
		else
			cout << path[i]+1 << " to ";
	}
	return min_path;
}

int main()
{
	/*
	float graph[][V]={
		{0,218.4,518.2,704.3,438.8},
		{218.4,0,735.9,807.7,568.8},
		{518.2,735.9,0,829.1,421.2},
		{704.3,807.7,829.1,0,1114.5},
		{438.8,568.8,421.2,1114.5,0}
	};

	float graph3[][V] = {
		{0, 6, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, 18, 8},
		{6, 0, 8, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, 2},
		{(float)INT_MAX, 8, 0, 8, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX},
		{(float)INT_MAX, (float)INT_MAX, 8, 0, 8, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX},
		{(float)INT_MAX, (float)INT_MAX, (float)INT_MAX, 8, 0, (float)INT_MAX, (float)INT_MAX, 20},
		{(float)INT_MAX, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, 0, 10, 12},
		{18, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, (float)INT_MAX, 10, 0, 12},
		{8, 2, (float)INT_MAX, (float)INT_MAX, 20, 12, 12, 0}
	};
	*/



	float graph2[][V] = {
		{0, 10, 16, 12, 8},
		{10, 0, 15, (float)INT_MAX, 20},
		{16, 15, 0, 10, (float)INT_MAX},
		{12, (float)INT_MAX, 10, 0, 8},
		{8, 20, (float)INT_MAX, 8, 0}
	};
	int start = 0;
	float sol = solution(graph2, start);

	cout << "Final Solution = " << sol << endl;

	return 0;
}
