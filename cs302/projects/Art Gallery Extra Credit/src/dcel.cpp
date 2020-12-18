#include "dcel.h"
#include <iostream>
#include <General.h>
#include <algorithm>
#include <stack>
#include <cmath>
#define PI 3.14159265 //might have to reduce the amount of digits in order to work with float?

DCELVertex::DCELVertex(Vertex* parent)
	: leaving(nullptr), Parent(parent)
{

}
//each vertex makes its leaving edge
//to make twins you must have first made all the DCEL vertices

HalfEdge::HalfEdge(DCELVertex* origin)
	: twin(nullptr), next(nullptr), _origin(origin)
{
	origin->outgoing.push_back(this);
}


float HalfEdge::toDeg(float rad)
{
	return rad * (180/PI);
}

void HalfEdge::setAngle()
{
	float dx = twin->origin()->parent()->x() - origin()->parent()->x();
	float dy = twin->origin()->parent()->y() - origin()->parent()->y();
	float length = sqrt(dx * dx + dy * dy);
	if (dy > 0) angle = toDeg(acos(dx/length));
	else angle = toDeg(2*PI - acos(dx/length));
}

bool angleCompare(HalfEdge* he1, HalfEdge* he2)
{
	return he1->angle < he2->angle;
}

DCELVertex* HalfEdge::origin()
{
	return _origin;
}

DCELVertex* DCEL::search(Vertex* parent)
{
    for (auto& v : vertexRecord)
        if (v->parent() == parent) return v;
    return nullptr;
}

DCEL::DCEL(Mesh* graph)
    : graph(graph)
{
	/* 1. Create all vertices
	 * 2. Create border HalfEdges (connecting them is optional)
	 * 3. Push all new HalfEdges to their origin vertex's container
	 * 3a. (3) is automatically done inside the HalfEdge construcor
	 * 4. Create HalfEdges from diagonals
	 * 5. Calculate all angle values for all HalfEdges
	 * 6. For every vertex, order their "outgoing" container in
	 *	  increasing order
	 * 7. For every vertex, connect their HalfEdges as such:
	 *	  edge[i].twin.next = edge[(i+1) % size]
	 * see HalfEdge class for why
	*/

	//(1), (2)
	//push vertices (and forward edges) in clockwise order
	Vertex* current = graph->vertices[0];
	DCELVertex* newVertex = nullptr;
	HalfEdge* newHE = nullptr;
	do {
		newVertex = new DCELVertex(current);
		newHE = new HalfEdge(newVertex);
		vertexRecord.push_back(newVertex);
		edgeRecord.push_back(newHE);
		newVertex->leaving = newHE; //also assigns the leaving edge
		current = current->next;
	} while (current != graph->vertices[0]);

	//(1), (2)
	//create twins of all the leaving edges
	size_t vertexCount = vertexRecord.size();
	HalfEdge* newTwin = nullptr;
	for (size_t i = 0; i < vertexCount; ++i) {
		//twin origin is the next vertex
		newTwin = new HalfEdge(vertexRecord[(i+1)%vertexCount]);
		edgeRecord.push_back(newTwin); //bookkeeping
		vertexRecord[i]->leaving->twin = newTwin; //connect twins to each other
		newTwin->twin = vertexRecord[i]->leaving;
	}

	//debug
	std::cout << "\nNew DCEL Vertices (in clockwise order):" << std::endl;
	for (auto& v : vertexRecord)
		std::cout << v->parent()->name << std::endl;

	//doubly connect all edges
	for (size_t i = 0; i < vertexCount; ++i) {
		vertexRecord[i]->leaving->next = vertexRecord[(i+1)%vertexCount]->leaving;
		vertexRecord[(i+1)%vertexCount]->leaving->twin->next = vertexRecord[i]->leaving->twin;
	}


	//debug
	//show that all border edges are linked
	std::cout << "\nBorder HalfEdges:" << std::endl;
	std::cout << "in clockwise order:" << std::endl;
	HalfEdge* output = edgeRecord[0];
	do {
		std::cout << output->origin()->parent()->name <<  std::endl;
		output = output->next;
	} while (output != edgeRecord[0]);
	output = edgeRecord[0]->twin;
	std::cout << "\nin CCW order:" << std::endl;
	do {
		std::cout << output->origin()->parent()->name <<  std::endl;
		output = output->next;
	} while (output != edgeRecord[0]->twin);

	//(4)
	//create edges from diagonals and assign twins
	//add diagonals to record
	//1. get the endpoints of the diagonal
	//2. search for DCEL vertex (make DCEL::search(Vertex*) which
	//	 looks for a DCELV with that parent)
	//3. create HE from that vertex and push it to newEdges
	//4. create twin HE from the other end of the diagonal and
	//	 attach the HE's together
	//5. do this for all diagonals
	vertexCount = graph->vertices.size();
	size_t edgeCount = graph->edges.size();
	DCELVertex* parent1 = nullptr;
	DCELVertex* parent2 = nullptr;
	HalfEdge* he1 = nullptr;
	HalfEdge* he2 = nullptr;
	for (size_t i = vertexCount; i < edgeCount; ++i) {
		parent1 = search(graph->edges[i]->endpoints[0]);
		parent2 = search(graph->edges[i]->endpoints[1]);
		he1 = new HalfEdge(parent1);
		he2 = new HalfEdge(parent2);
		he1->twin = he2;
		he2->twin = he1;
		newEdges.push_back(he1);
		newEdges.push_back(he2);
	}

	//(5), (6), (7)
	for (auto& v : vertexRecord) {
		for (auto& he : v->outgoing)
			he->setAngle();
		std::sort(v->outgoing.begin(), v->outgoing.end(), angleCompare);
		edgeCount = v->outgoing.size();
		for (size_t i = 0; i < edgeCount; ++i)
			v->outgoing[(i+1) % edgeCount]->twin->next = v->outgoing[i];
	}

	//testing halfedges
	std::cout << "\nHalfEdge traces:" << std::endl;
	for (auto& he : newEdges) {
		output = he; //"output" variable from line 92
		do {
			std::cout << output->origin()->parent()->name << "   ";
			output = output->next;
		} while (output != he);
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//make faces
	edgeCount = newEdges.size();
	HalfEdge* newFace = nullptr;
	HalfEdge* travel = nullptr;
	for (size_t i = 0; i < edgeCount; ++i) {
		newFace = newEdges[i];
		travel = newFace->next;
		do {
			//If you find another newEdge while traveling the face,
			//that halfedge cannot point to a face

			//You are only searching the edges "after" the one you
			//want to make a face out of

			if (search(i+1, edgeCount, travel)) {
				break;
			}
			travel = travel->next;
		} while (travel != newFace);
		if (travel == newFace) faceRecord.push_back(new Face(newFace));
	}

	//If the inputted polygon is already monotone, just make any
	//halfedge as the face
	vertexCount = graph->vertices.size();
	edgeCount = graph->edges.size();
	if (vertexCount == edgeCount) faceRecord.push_back(new Face(edgeRecord[0]->twin));

	//debug
	std::cout << "\nMesh subdivisions are: (from top vertex to bottom)" << std::endl;
	for (auto& f : faceRecord) {
		for (auto& v : f->vertices)
			std::cout << v->parent()->name << " / ";
		std::cout << std::endl;
	}
}

DCEL::~DCEL()
{
    for (auto& v : vertexRecord)
        delete v;
    for (auto& he : edgeRecord)
        delete he;
    for (auto& he : newEdges)
        delete he;
    for (auto& f : faceRecord)
        delete f;
}

bool DCEL::search(size_t start, size_t end, HalfEdge* value)
{
    for (size_t i = start; i < end; ++i)
		if (newEdges[i] == value) return true;
    return false;
}

void Face::createVertices(std::vector<DCELVertex *>& vertexList)
{
    HalfEdge* travel = bound;
    do {
        vertexList.push_back(travel->origin());
        travel = travel->next;
	} while (travel != bound);
}

Face::Face(HalfEdge* bound)
    : bound(bound)
{
	std::cout << "New face made!" << std::endl;
    createVertices(vertices);

    //sort vertices for the sweep-line
	std::sort(vertices.begin(), vertices.end(), DCEL_y_compare);
}

void DCEL::triangulateFace(Face* face)
{
	Edge* output = nullptr;


    size_t vertexCount = face->vertices.size();
    if (vertexCount == 3) return;
    std::vector<DCELVertex*> leftChain;

	//Right chain technically isn't needed
	std::vector<DCELVertex*> rightChain;
    face->createChains(leftChain, rightChain);
    std::stack<DCELVertex*> untreated;
    DCELVertex* connect = nullptr;
    DCELVertex* previous = nullptr;
	DCELVertex* current = nullptr;
    untreated.push(face->vertices[0]);
    untreated.push(face->vertices[1]);
    for (size_t i = 2; i < vertexCount-1; ++i) {
		current = face->vertices[i];
		if (!(face->onSameChain(current, untreated.top(), leftChain))) {
            previous = untreated.top();
            while (!untreated.empty()) {
                connect = untreated.top();
				//if you can see the top, connect to it and pop
				//otherwise, pop until everything is empty
				if (sees(current, connect, face)) {
					graph->diag(current->parent(), connect->parent());
					output = graph->edges[graph->edges.size() - 1];
					std::cout << "New edge between "
							  << output->endpoints[0]->name
							  << " and "
							  << output->endpoints[1]->name
							  << std::endl;
				}
				untreated.pop();
            }
			//Push the current vertex and the one before
            untreated.push(previous);
			untreated.push(current);
		} else {
			//Top and current vertex are on the same chain
            connect = untreated.top();
            untreated.pop();

			//If the chain forms a straight line, dcel.sees()
			//and mesh.diag() are both safe operations, meaning
			//they will not create an overlapping diagonal
			while (!untreated.empty() && sees(current, untreated.top(), face)) {
                connect = untreated.top();
                untreated.pop();
				graph->diag(current->parent(), connect->parent());

				output = graph->edges[graph->edges.size() - 1];
				std::cout << "New edge between "
						  << output->endpoints[0]->name
						  << " and "
						  << output->endpoints[1]->name
						  << std::endl;

            }
            untreated.push(connect);
			untreated.push(current);
        }
    }
    untreated.pop();

	/*
	//This might have to be rewritten to connect to everything that it can, which will kill time
	//complexity however it will fix the problem of non-strict monotone polygons (see rewritten ver. below)
	size_t leftoverCount = untreated.size();
	//Connect all leftover vertices in stack to the
	//bottom vertex, except for the first and last members in the stack
	for (size_t i = 1; i < leftoverCount; ++i) {
		graph->diag(face->vertices[vertexCount-1]->parent(), untreated.top()->parent());

		untreated.pop();

		output = graph->edges.back();
		std::cout << "New edge between "
				  << output->endpoints[0]->name
				  << " and "
				  << output->endpoints[1]->name
				  << std::endl;
    }
	*/



	for (size_t i = 1; i < vertexCount-1; ++i) {
		if (sees(face->vertices[vertexCount-1], face->vertices[i], face)) {
			graph->diag(face->vertices[vertexCount-1]->parent(), face->vertices[i]->parent());

			output = graph->edges.back();
			std::cout << "New edge between "
					  << output->endpoints[0]->name
					  << " and "
					  << output->endpoints[1]->name
					  << std::endl;
		}
	}
}

bool Face::createsExteriorEdge(DCELVertex* A, DCELVertex* B)
{
	//https://w3.cs.jmu.edu/bowersjc/page/courses/spring17/cs480/labs/triangulation/
	/* 1. Find the "previous" and "next" vertices of [A]
	 * 2. Determine the "type" of A (convex = <180, reflex = >=180)
	 * 2a. A is convex if A.prev>>A>>A.next is a left hand turn
	 *	   (use cross product)
	 * 3a. if convex, edge is [INSIDE] if A.prev>>A>>B [AND] B>>A>>A.next
	 *     are both [LEFT HAND TURNS] (use cross product)
	 * 3b. if reflex, edge is [OUTSIDE] if A.next>>A>>B [AND] B>>A>>A.prev
	 *     are both [LEFT HAND TURNS] (use cross product)
	*/
	//Sidenote: we do not have to consider the case where this new edge
	//is coincident to any other edges of the polygon/face because that
	//case is already handled by ::segmentsIntersect()
	HalfEdge* travel = bound;
	while (travel->next->origin() != A) {
		travel = travel->next;
	}
	DCELVertex* previous = travel->origin();
	DCELVertex* next = travel->next->next->origin();
	float type = crossProduct(previous->parent(), A->parent(), next->parent());
	if (type > 0) { //convex vertex
		if (crossProduct(previous->parent(), A->parent(), B->parent()) > 0 &&
			crossProduct(B->parent(), A->parent(), next->parent()) > 0) return false; //the line is inside, so we return false
		return true;
	}
	//reflex vertex
	if (crossProduct(next->parent(), A->parent(), B->parent()) > 0 &&
		crossProduct(B->parent(), A->parent(), previous->parent()) > 0) return true;
	return false;
}

bool DCEL::sees(DCELVertex* v1, DCELVertex* v2, Face* F)
{
	//check if the new edge lies outside of the face
	if (graph->areConnected(v1->parent(), v2->parent())) return false;
	if (F->createsExteriorEdge(v1, v2)) return false;
	Vertex* e1a = v1->parent();
    Vertex* e1b = v2->parent();
    Vertex* e2a = nullptr;
    Vertex* e2b = nullptr;
	for (auto& e : graph->edges) {
		e2a = e->endpoints[0];
		e2b = e->endpoints[1];
        if (segmentsIntersect(e1a, e1b, e2a, e2b)) return false;
    }
    return true;
}

void Face::createChains(std::vector<DCELVertex *>& left, std::vector<DCELVertex *>& right)
{
    std::vector<DCELVertex*> temp;
    HalfEdge* travel = bound;

	//Set travel to the highest vertex
	while (travel->origin() != vertices[0])
        travel = travel->next;

	//Get the vertex after the highest
    travel = travel->next;

	//Push vertices along the left chain except the last one
	while (travel->origin() != vertices[vertices.size()-1]) {
        left.push_back(travel->origin());
        travel = travel->next;
    }
    travel = travel->next;

	//Travel up the right chain starting from the bottom

	//Not sure if this is needed as you will be searching
	//the chains so u don't need them in order
	while (travel->origin() != vertices[0]) {

        temp.push_back(travel->origin());
        travel = travel->next;
    }

	//conversion to int because size_t is unsafe if size = 0 or 1
	for (int i = int(temp.size())-1; i >= 0; --i)
        right.push_back(temp[i]);
}


//It doesn't matter what chain you input here the result will
//still be the same
bool Face::onSameChain(DCELVertex* v1, DCELVertex* v2, std::vector<DCELVertex *>& chain)
{
    bool v1check = false, v2check = false;
    for (auto& v : chain) {
        if (v == v1) v1check = true;
        if (v == v2) v2check = true;
    }
	return (v1check == v2check);
}
