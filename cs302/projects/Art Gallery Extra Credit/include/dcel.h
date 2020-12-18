#ifndef DCEL_H
#define DCEL_H
#include "vertex.h"
#include "edge.h"
#include "mesh.h"

class HalfEdge;
class Face;
class DCELVertex
{
	public:
		//DCEL vertex should only destroy its leaving ptr
		DCELVertex(Vertex* parent);

		//Memory is managed through the DCEL class
		~DCELVertex() {};

		//Used to initialize the DCEL vertexRecord
		HalfEdge* leaving;

		//Stores all HalfEdges whose origin is at this vertex
		std::vector<HalfEdge*> outgoing;

		//This could be made obsolete by making the parent public
		Vertex* parent() {return Parent;};
	private:
		Vertex* Parent;
};

/**
 * @brief angleCompare
 * Used to order the "outgoing" HalfEdges of a DCELVertex
 * @param he1
 * @param he2
 * @return
 */
bool angleCompare(HalfEdge* he1, HalfEdge* he2);

class HalfEdge
{
	public:		
		HalfEdge(DCELVertex*);
		~HalfEdge() {};
		HalfEdge* twin = nullptr;
		HalfEdge* next = nullptr;

		//Returns _origin; again could be made obsolete
		DCELVertex* origin();

		//Used to connect all halfedges correctly
		//https://stackoverflow.com/questions/56980195/adding-edges-dynamically-in-a-dcel-half-edge-based-graph
		float angle;
		void setAngle();
		float toDeg(float rad);

	private:
		DCELVertex* _origin;
};


class Face
{
	public:
		Face(HalfEdge* bound);
		~Face() {};

		//Container for all the vertices that make up the face
		//Stores vertices in CCW order
		std::vector<DCELVertex*> vertices;

		//Creates two lists of vertices, one to describe
		//the left and right halves of the polygon
		void createChains(std::vector<DCELVertex*>&, std::vector<DCELVertex*>&);

		//Determines if two vertices are on the same chain
		bool onSameChain(DCELVertex*, DCELVertex*, std::vector<DCELVertex*>&);

		//Helper function for ctor
		void createVertices(std::vector<DCELVertex*>&);


		//Determines if the edge formed by two vertices lies
		//on the inside or the outside of the polygon
		//Used in DCEL::sees
		//Returns true if the edge lies outside
		bool createsExteriorEdge(DCELVertex*, DCELVertex*);

	private:
		//A halfedge that is part of the border of the polygon
		HalfEdge* bound;
};

//Uses containment
class DCEL
{
	public:
		DCEL(Mesh* graph);
		~DCEL();
		std::vector<DCELVertex*> vertexRecord;

		//for bookkeeping so that we can delete all edges later
		std::vector<HalfEdge*> edgeRecord;

		//Holds the halfedges created from the added diagonals
		std::vector<HalfEdge*> newEdges;

		//edgeRecord and newEdges do not have overlapping elements

		//Holds the subpolygons created by the added diagonals
		std::vector<Face*> faceRecord;

		//Returns the DCELVertex in the DCEL whose parent
		//equals that of the input
		DCELVertex* search(Vertex*);

		//Checks if there is a HalfEdge of value within
		//[start, end) of newEdges
		bool search(size_t start, size_t end, HalfEdge* value);

		//See documentation for monotone triangulation
		void triangulateFace(Face*);

		//Looks thru all face edges and checks if the diagonal
		//created intersects any of them
		bool sees(DCELVertex*, DCELVertex*, Face*);

	private:
		Mesh* graph;


};

#endif // DCEL_H
