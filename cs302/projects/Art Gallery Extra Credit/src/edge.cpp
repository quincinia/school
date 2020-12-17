#include "edge.h"
#include <cmath> //fabs

//Because we set the orientation of the mesh before
//we make the edges, the edges will also be oriented
Edge::Edge(Vertex* e1, Vertex* e2)
{
	endpoints[0] = e1;
	endpoints[1] = e2;
}

bool Edge::contains(Vertex* v)
{
	return (endpoints[0] == v || endpoints[1] == v);
}

bool Edge::contains(float y)
{
	if (endpoints[0]->y() == y || endpoints[1]->y() == y) return true;
	if (endpoints[0]->y() > y && endpoints[1]->y() < y) return true;
	if (endpoints[0]->y() < y && endpoints[1]->y() > y) return true;
	return false;
}

//Edges are guaranteed to cross when this function is called
float Edge::intercepts(float x, float y)
{
	//x1 + t(x2-x1) = xi
	//y1 + t(y2-y1) = yi = given
	//t = (yi-y1)/(y2-y1)
	//when y2 = y1, segment is horizontal
	//when horizontal, return the endpoint closest to the tested point
	float x1 = this->endpoints[0]->x();
	float y1 = this->endpoints[0]->y();
	float x2 = this->endpoints[1]->x();
	float y2 = this->endpoints[1]->y();
	float t;
	if ((y2-y1) == 0) {
		if (fabs(x1 - x) < fabs(x2 - x)) return x1;
		else return x2;
	}
	t = (y-y1)/(y2-y1);
	return (x1 + t*(x2-x1));
}

Vertex* Edge::top()
{
	if (endpoints[0]->y() > endpoints[1]->y()) return endpoints[0];
	return endpoints[1];
}

Vertex* Edge::bottom()
{
	if (endpoints[0]->y() < endpoints[1]->y()) return endpoints[0];
	return endpoints[1];
}
