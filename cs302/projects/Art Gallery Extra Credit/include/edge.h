#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

class Edge
{
	friend class HalfEdge;
	public:
		Edge(Vertex* e1, Vertex* e2);

		//Made public for easy access
		Vertex* endpoints[2];

		//Used in makeMonotone
		Vertex* helper = nullptr;

		//Returns true if the vertex is one of its endpoints
		bool contains(Vertex*);

		//Returns true if the endpoints are above and below
		//a certain y-value
		bool contains(float);

		//Returns the x-value of the intersection of this
		//edge and an inputted point
		float intercepts(float, float);

		Vertex* top(); //used in Mesh::diag
		Vertex* bottom(); //used in Mesh::diag
};

#endif // EDGE_H
