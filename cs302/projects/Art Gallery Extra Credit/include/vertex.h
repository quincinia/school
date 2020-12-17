#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <vector>
#include <string>
class Edge;
class Vertex
{
	friend class DCELVertex;
    public:
		//Used to generate unique vertex names
		static int count;
		std::string name;

		Vertex(float x, float y);
		~Vertex(); //all memory is handled by the Mesh class

		//Sets edge helper to this
		void help(Edge* e);

		//Looks through the edge record and determines if this
		//vertex can help any of them
		Edge* findHelper(std::vector<Edge*>);

		float x() const {return X;};
		float y() const {return Y;};
		char type() const {return Type;};

		//Used in ::classifyVertices
		void setType(char);

		//Collection of all vertices this vertex shares an edge with
		std::vector<Vertex*> partners;

		//Clockwise next
		Vertex* next = nullptr;

		//CCW prev
		Vertex* prev = nullptr;


		Edge* helper = nullptr;
		Edge* nextEdge = nullptr; //used in makeMonotone


		int color;

		friend std::ostream& operator<<(std::ostream&, const Vertex&);

	private:
		float X, Y;
		char Type;
		//5 types
		// b - start
		// s - split
		// e - end
		// m - merge
		// r - regular/normal

		//Determines if the vertex has a left neighbor
		//at the same y-value
		bool hasHorizontalLeft();

		//To only be used with regular vertices
		bool hasLeftInterior();
};

#endif // VERTEX_H
