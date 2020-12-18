#ifndef MESH_H
#define MESH_H
#include "vertex.h"
#include "edge.h"

//This is the "master" mesh; it will contain all the data of the graph
//Mesh will perform the destruction of the allocated vertices and edges,
//all other classes that may have references to these vertices or edges will not free that memory
class Mesh
{
	public:
		Mesh();
		~Mesh();

		//Check if vertex has been treated, then check
		//vertex type, then attach to top or bottom of edge
		void diag(Edge*, Vertex*);

		//Unsafe connection, used when diagonals will
		//not overlap current edges
		void diag(Vertex*, Vertex*);

		//Stores vertices of the mesh
		std::vector<Vertex*> vertices;

		//Stores edges of the mesh
		std::vector<Edge*> edges;

		//Returns true if vertices are connected along a
		//boundary, NOT a diagonal
		bool areConnected(Vertex*, Vertex*);
};

#endif // MESH_H
