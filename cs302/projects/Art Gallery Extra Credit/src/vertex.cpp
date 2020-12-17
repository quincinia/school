#include "vertex.h"
#include "edge.h"
#include <cmath> //fabs

int Vertex::count = 0;

Vertex::Vertex(float x, float y)
	: color(0), X(x), Y(y), Type(' ')
{
	//All other data members have been initialized inside the class
	name = "V" + std::to_string(count++);
}

Vertex::~Vertex()
{

}

void Vertex::help(Edge *e)
{
	e->helper = this;
}

void Vertex::setType(char t)
{
	Type = t;
}

Edge* Vertex::findHelper(std::vector<Edge*> edges)
{
	//Find all edges s.t. the endpoints lie above and below this->y and
	//that the intersection point of the horizonal line and the edge is
	//to the left of the vertex

	//All edges that contain this vertex are ignored

	//Return the edge whose intersection point is closest to the vertex

	//If the vertex is part of a horizontal line segment...
	//		return null if its left neighbor is at the same y-value

	//If the exterior of the polygon lies to the left of the vertex, return nullptr

	//Rule out fringe cases that do not have helpers
	if (hasHorizontalLeft()) return nullptr;
	if (Type == 'r' && !hasLeftInterior()) return nullptr;

	Edge* helper = nullptr;
	float old_x_intersection, new_x_intersection;
	//Technically you only have to search the border edges because
	//your sweep line is guaranteed to never hit a diagonal
	for (auto& e : edges) {

		//Ignore all edges that have this vertex as an endpoint
		if (e->contains(this)) continue;

		//Ignore edges that do not intersect the sweep line
		if (!(e->contains(this->y()))) continue;

		//Ignore edges that intersect to the right of this vertex
		new_x_intersection = e->intercepts(this->x(), this->y());
		if (new_x_intersection > this->x()) continue;


		if (helper == nullptr) {
			//This should only be run once to get an initial value for the
			//old intersection
			helper = e;
			old_x_intersection = new_x_intersection;

		} else {
			//New intersection point is closer than the old one
			if (new_x_intersection > old_x_intersection) {
				helper = e;
				old_x_intersection = new_x_intersection;
			}
		}
	}

	//If the helper edge has an endpoint on the same y-value as the vertex,
	//the vertex will always attach to (edge.endpoint = y).nextEdge
	/*if (helper.type == horizontal) {
		v = helper.find_closer_endpoint(this);
		if (v.nextEdge != horizontal) helper = v.nextEdge;
		else helper = v.prevEdge;
	}*/

	//Another implementation that does not require additional functions/members
	Vertex* v = nullptr;
	if (helper->endpoints[0]->y() == helper->endpoints[1]->y()) {
		v = (helper->endpoints[0]->x() > helper->endpoints[1]->x()) ? helper->endpoints[0] : helper->endpoints[1]; //find closer endpoint
		if (v->y() != v->next->y()) helper = v->nextEdge;
		else helper = v->prev->nextEdge;
	}

	return helper;
}

bool Vertex::hasHorizontalLeft()
{
	if (prev->x() < X && prev->y() == Y) return true;
	if (next->x() < X && next->y() == Y) return true;
	return false;
}

bool Vertex::hasLeftInterior()
{
	//Vertices should flow downward
	return (prev->y() > next->y());
}

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
	os << "{" << v.x() << ", " << v.y() << "}";
	return os;
}
