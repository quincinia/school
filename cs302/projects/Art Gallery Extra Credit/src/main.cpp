#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm> //for std::sort, maybe put this inside General
#include <General.h>
#include <dcel.h> //decl contains all the other types
using namespace std;
int main() {
	string input;
	char junk, end;
	float x, y;
	Mesh master;


	/*		Add vertices to mesh		*/

	cout << "Enter vertex list:" << endl;
	do {
		scanf("%c(%f, %f)%c", &junk, &x, &y, &end);
		master.vertices.push_back(new Vertex(x, y));
	} while (end != '}');
	//scanning and output are [GOOD]

	//debug
	cout << "\nScanned vertices:" << endl;
	for (auto& v : master.vertices)
		cout << v->name << ": " << *v << endl;
	//return 0;

//--------------------------------------------------


	/*		Assign neighbors to each vertex		*/

	size_t vertexCount = master.vertices.size();
	for (size_t i = 0; i < vertexCount; ++i) {
		master.vertices[i]->next = master.vertices[(i+1)%vertexCount];
		if (i == 0) master.vertices[i]->prev = master.vertices[vertexCount - 1];
		else master.vertices[i]->prev = master.vertices[i-1];
	}
	//neighbors are [GOOD]

	//debug
	cout << "\nNeighbors:" << endl;
	cout << "Prev | Current | Next" << endl;
	for (auto& v : master.vertices)
		cout << v->prev->name << "   " << v->name << "   " << v->next->name << endl;
	//return 0;
//------------------------------------------------------------------------------


	/*		Impose direction to mesh		*/
	/*		- boundary of the polygon will flow CLOCKWISE		*/

	//clockwise orientation [GOOD]

	cout << "\nSetting clockwise orientation..." << endl;
	setClockwise(master.vertices);

	//debug
	cout << "\nIn clockwise order:" << endl;
	cout << "Prev | Current | Next" << endl;
	for (auto& v : master.vertices)
		cout << v->prev->name << "\t" << v->name << "\t" << v->next->name << endl;
	//return 0;
//-----------------------------------------------------------------


	/*		Add edges to mesh, add next edge to vertex		*/
	//this step and the above are interchangable(?)
	Edge* insert = nullptr;
	for (auto& v : master.vertices) {
		insert = new Edge(v, v->next);
		master.edges.push_back(insert);
		v->nextEdge = insert;
	}

	//edges are [GOOD]

	//debug
	cout << "\nEdges:" << endl;
	for (auto& e : master.edges)
		cout << "From: " << e->endpoints[0]->name << " to " << e->endpoints[1]->name << endl;
	//return 0;
//---------------------------------------------------


	/*		Assign vertex types		*/

	cV2(master.vertices);

	//vertices are [TBD] (check merge case)

	//debug
	cout << "\nVertex types:" << endl;
	for (auto& v : master.vertices)
		cout << v->name << ": Type " << v->type() << endl;
	//return 0;
//------------------------------------


	/*		Partition polygon/mesh into y-monotone pieces		*/
	cout << "\nSorting vertices..." << endl;

	//Sort vertices to prep for sweep-line
	//See General for y_compare
	std::sort(master.vertices.begin(), master.vertices.end(), y_compare);

	cout << "Adding diagonals..." << endl;
	makeMonotone(master);

	//diagonals are [TBD] (test weird fringe cases where helper is horizontal)

	//debug
	cout << "\nAdded diagonals: " << endl;
	size_t debugVCount = master.vertices.size();
	size_t debugECount = master.edges.size();
	for (size_t i = debugVCount; i < debugECount; ++i)
		cout << "From: " << master.edges[i]->endpoints[0]->name << " to " << master.edges[i]->endpoints[1]->name << endl;
	//return 0;
//------------------------------------------------------------------------


	/*		Convert mesh to DCEL		*/
	cout << "\nCreating DCEL..." << endl;
	DCEL partitions(&master);

	//DCEL conversion is [GOOD]
	//return 0;
//----------------------------------------


	/*		Triangulate all faces		*/
	cout << "\nTriangulating polygon..." << endl;
	for (auto& f : partitions.faceRecord)
		partitions.triangulateFace(f);

	//Triangulations are [GOOD] (im like 99% sure)
	//return 0;
//----------------------------------------


	/*		Prep vertices for coloring		*/
	//Can't really come up with any debugging statements other
	//than just printing out all the vertices and their partners
	cout << "\nPrepping vertices for coloring..." << endl;
	size_t edgeCount = master.edges.size();
	Vertex* v1 = nullptr;
	Vertex* v2 = nullptr;

	for (size_t i = 0; i < edgeCount; ++i) {
		v1 = master.edges[i]->endpoints[0];
		v2 = master.edges[i]->endpoints[1];
		v1->partners.push_back(v2);
		v2->partners.push_back(v1);
	}

	//Sort vertex partners for use in set_intersection
	for (auto& v : master.vertices)
		std::sort(v->partners.begin(), v->partners.end(), y_compare);

//--------------------------------------------


	/*		Color all vertices		*/
	cout << "\nColoring vertices..." << endl;
	Vertex* current = master.vertices[0];

	//initialize coloring
	current->color = 1;
	current->next->color = 2;

	colorRec(current, current->next);
	/*
	do {
		color(current, current->next);
		current = current->next;
	} while (current != master.vertices[0]);
	*/

	Vertex* outputVertex = master.vertices[0];
	do {
		cout << outputVertex->name << ": " << outputVertex->color << endl;
		outputVertex = outputVertex->next;
	} while (outputVertex != master.vertices[0]);
//------------------------------------


	/*		Determine least used color		*/
	int redCount = 0, blueCount = 0, greenCount = 0;
	for (auto& v : master.vertices) {
		switch (v->color) {
			case 1:
				++redCount;
			break;

			case 2:
				++greenCount;
			break;

			case 3:
				++blueCount;
			break;
		}
	}
	int leastUsed = smallestColor(redCount, greenCount, blueCount);
	string colorName;
	switch (leastUsed) {
		case 1:
			colorName = "1, 0, 0"; //red
		break;

		case 2:
			colorName = "0, 1, 0"; //green
		break;

		case 3:
			colorName = "0, 0, 1"; //blue
		break;
	}

	cout << "\nLeast used color is: " << colorName << " (" << leastUsed << ")" << endl;
//--------------------------------------------


	/*		Output solution		*/
	//Print to console
	//Will hold the vertices that need to be colored
	vector<string> colorVertices;
	cout << "Vertex count (n): " << master.vertices.size() << endl;
	cout << "Worst-case solution (n/3): "
		 << master.vertices.size()/3 << endl;
	cout << "Solution Vertices:" << endl;
	for (auto& v : master.vertices) {
		if (v->color == leastUsed) {
			cout << v->name << endl;
			colorVertices.push_back(v->name);
		}
	}
	cout << "\nAdded Diagonals:" << endl;
	vertexCount = master.vertices.size();
	edgeCount = master.edges.size();
	for (size_t i = vertexCount; i < edgeCount; ++i) {
		cout << "From "
			 << master.edges[i]->endpoints[0]->name
			 << " to "
			 << master.edges[i]->endpoints[1]->name
			 << endl;
	}



	//Print GeoGebra commands to file
	cout << "\nWriting solution to file..." << endl;
	ofstream output("output.txt");
	output << "To use, copy each command line [IN ORDER] into Geogebra" << endl;
	output << "Note: you can use [Shift + End] to select everything after the cursor\n" << endl;

	//Create all vertices
	output << "Execute({";
	for (size_t i = 0; i < vertexCount-1; ++i) {
		output << "\"" << master.vertices[i]->name
			   << " = Point(" << *master.vertices[i]
			   << ")\", ";
	}
	output << "\"" << master.vertices[vertexCount-1]->name
		   << " = Point(" << *master.vertices[vertexCount-1]
		   << ")\"})" << endl;

	//To reduce confusion, only the solution vertices will be colored
	output << "Execute({";
	vertexCount = colorVertices.size();

	//Color solution vertices
	for (size_t i = 0; i < vertexCount-1; ++i) {
		output << "\"SetColor(" << colorVertices[i]
			   << ", " << colorName << ")\", ";
	}
	output << "\"SetColor(" << colorVertices[vertexCount-1]
		   << ", " << colorName << ")\"})" << endl;


	//Create triangulation edges
	vertexCount = master.vertices.size();
	edgeCount = master.edges.size();
	output << "Execute({";
	for (size_t i = vertexCount; i < edgeCount-1; ++i) {
		output << "\"Segment(" << master.edges[i]->endpoints[0]->name
			   << ", " << master.edges[i]->endpoints[1]->name << ")\", ";
	}
	output << "\"Segment(" << master.edges[edgeCount-1]->endpoints[0]->name
		   << ", " << master.edges[edgeCount-1]->endpoints[1]->name << ")\"})"
		   << endl;
//--------------------------------
	cout << "Finished" << endl;
	return 0;
}
