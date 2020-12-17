#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	for (auto& v : vertices)
		delete v;
	for (auto& e : edges)
		delete e;
}

void Mesh::diag(Edge * edge, Vertex * v)
{
	//Check if the start/split vertices have been treated already or not
	//Technically the makeMonotone already checks for this by removing
	//the vertex from its helping status and clearing the edge of its helpers
	if (v == nullptr) return;
	switch (v->type()) {
		case 'm': case 'r': //for fringe cases
			if (!areConnected(edge->bottom(), v))
				edges.push_back(new Edge(edge->bottom(), v));
		break;

		case 's':
			//maybe add another connected check
			edges.push_back(new Edge(edge->top(), v));
		break;
	}
}

void Mesh::diag(Vertex * e1, Vertex * e2)
{
	if (e2 == nullptr) return;
	if (areConnected(e1, e2)) return;
	edges.push_back(new Edge(e1, e2));
}

bool Mesh::areConnected(Vertex * v1, Vertex * v2)
{
	return (v1->next == v2 || v1->prev == v2);
}
