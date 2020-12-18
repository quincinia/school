#include <General.h>
#include <cmath>
#include <utility>
using namespace std;

void setClockwise(std::vector<Vertex*> input)
{
	size_t vertexCount = input.size();
	Vertex* bearing = input[0];
	for (size_t i = 1; i < vertexCount; ++i) { //find highest vertex
		if (input[i]->y() > bearing->y()) {
			bearing = input[i];
			continue;
		}
		if (input[i]->y() == bearing->y()) {
			if (input[i]->x() > bearing->x()) {
				bearing = input[i];
			}
		}
	}

	cout << "Highest vertex: " << bearing->name << endl;

	//x component is in index 0, y component in index 1
	//vectors from bearing to its neighbors
	float nextVector[2];
	float prevVector[2];
	nextVector[0] = bearing->next->x() - bearing->x();
	nextVector[1] = bearing->next->y() - bearing->y();
	float magNV = hypot(nextVector[0], nextVector[1]); //magnitude

	prevVector[0] = bearing->prev->x() - bearing->x();
	prevVector[1] = bearing->prev->y() - bearing->y();
	float magPV = hypot(prevVector[0], prevVector[1]);

	cout << "X-component of 'Prev' vector: " << prevVector[0]/magPV << endl;
	cout << "X-component of 'Next' vector: " << nextVector[0]/magNV << endl;

	if (prevVector[0]/magPV > nextVector[0]/magNV) {
		cout << "Swap made!" << endl;
	//because we have an (array) of pointers, we can edit the Vertex objects directly and they will be changed in the master mesh
	//if one of the vertices has the wrong orientation, then all of them do
		for (auto& v : input)
			swap(v->next, v->prev);
	}

}

float crossProduct(Vertex* prev, Vertex* mid, Vertex* next)
{
	float nextVector[2]; //from mid to next
	float prevVector[2]; //from prev to mid
	nextVector[0] = next->x() - mid->x();
	nextVector[1] = next->y() - mid->y();
	prevVector[0] = mid->x() - prev->x();
	prevVector[1] = mid->y() - prev->y();
	//Negative value is a right hand turn; positive a left hand turn
	return (prevVector[0]*nextVector[1] - prevVector[1]*nextVector[0]);
}

void cV2(std::vector<Vertex*> input)
{
	for (auto& v : input)
	{
		bool abovePrev = (v->y() > v->prev->y()) ||
						 ((v->y() == v->prev->y()) && (v->x() < v->prev->x()));
		bool aboveNext = (v->y() > v->next->y()) ||
						 ((v->y() == v->next->y()) && (v->x() < v->next->x()));

		if (abovePrev != aboveNext) {
			v->setType('r');
			continue;
		}

		float turn = crossProduct(v->prev, v, v->next);

		if (abovePrev && aboveNext) {
			if (turn < 0) {
				v->setType('b');
				continue;
			} else {
				v->setType('s');
				continue;
			}
		} else { //below both
			if (turn < 0) {
				v->setType('e');
				continue;
			} else {
				v->setType('m');
				continue;
			}
		}
	}
}


void classifyVertices(std::vector<Vertex*> input)
{
	float nextVector[2]; //from vertex to vertex->next
	float prevVector[2]; //from prev to vertex
	for (auto& v : input) {

		if ((v->y() == v->next->y()) || (v->y() == v->prev->y())) { //checks for regular/normal
			v->setType('r');
			continue;
		}
		if (v->y() > v->prev->y() && v->next->y() > v->y()) {
			v->setType('r');
			continue;
		}
		nextVector[0] = v->next->x() - v->x();
		nextVector[1] = v->next->y() - v->y();
		prevVector[0] = v->x() - v->prev->x();
		prevVector[1] = v->y() - v->prev->y();

		//prevV cross nextV
		if (v->y() > v->next->y()) { //if true, v is either start or split
			if (prevVector[0]*nextVector[1] - prevVector[1]*nextVector[0] < 0) { //if true, v is start
				v->setType('b');
				continue;
			}
			v->setType('s'); //otherwise, v is split
			continue;
		}


		//if not start or split, then it is either end or merge
		if (prevVector[0]*nextVector[1] - prevVector[1]*nextVector[0] < 0) { //if true, v is end
			v->setType('e');
			continue;
		}

		v->setType('m');

	}
}

void makeMonotone(Mesh& polygon)
{
	Vertex* prevHelper = nullptr; //for regular vertices
	Vertex* nextEdgeHelper = nullptr; //for merge vertices
	for (auto& v : polygon.vertices) {
		switch (v->type()) {
			case 'b':
				continue; //no events can happen at start vertices
			break;

			case 'r':
				v->helper = v->findHelper(polygon.edges);
				if (v->helper == nullptr) { //if it doesn't have a helper, then it is the end of an edge
					polygon.diag(v->nextEdge, v->nextEdge->helper);
				} else {
					prevHelper = v->helper->helper;
					if (prevHelper)
						if (prevHelper->type() == 'm') polygon.diag(v, prevHelper);
					v->help(v->helper);
				}
			break;

			case 's':
				v->helper = v->findHelper(polygon.edges);
				//split vertices are guaranteed to find a helper so we don't need to check if its null
				if (v->helper->helper != nullptr) { //previous helper exists
					polygon.diag(v, v->helper->helper); //connects to previous helper
					//remove all helpers from v->helper (?)
					v->helper->helper = nullptr;
				} else {
					v->help(v->helper);
				}
			break;

			case 'm':
				v->helper = v->findHelper(polygon.edges);
				if (v->helper) v->help(v->helper);

				//all other cases should handle merge
				//merge vertices are also the end of an edge so the
				//appropriate action needs to be taken
				nextEdgeHelper = v->nextEdge->helper;
				if (nextEdgeHelper) { //helper exists
					if (nextEdgeHelper->type() == 'r') polygon.diag(v, nextEdgeHelper);
					else polygon.diag(v->nextEdge, nextEdgeHelper);
				}
			break;

			case 'e':
				polygon.diag(v->nextEdge, v->nextEdge->helper);
			break;
		}
	}
}

bool segmentsIntersect(Vertex* edge1a, Vertex* edge1b, Vertex* edge2a, Vertex* edge2b)
{
	//If the testing segment and an existing segment share a vertex, then
	//the two endpoints of the testing segment can still see each other***
	//***except in the case of coincidence


	float x1 = edge1a->x();
	float y1 = edge1a->y();
	float x2 = edge1b->x();
	float y2 = edge1b->y();

	float x3 = edge2a->x();
	float y3 = edge2a->y();
	float x4 = edge2b->x();
	float y4 = edge2b->y();

	float det1 = (x1-x3)*(y3-y4) - (y1-y3)*(x3-x4);
	float det2 = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
	float det3 = (y1-y2)*(x1-x3) - (x1-x2)*(y1-y3);
	float det4 = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);

	//if the two edges share a vertex, then they either aren't crossing
	//or they're coincident
	Vertex* shared = findSharedVertex(edge1a, edge1b, edge2a, edge2b);
	if (shared) {

		//Coincident if det2 and det4 are 0 and unit vectors point in
		//opposite directions
		if ((det2 == 0) && (det4 == 0)) {
			Vertex* start = (edge1a != shared) ? edge1a : edge1b;
			Vertex* end = (edge2a != shared) ? edge2a : edge2b;
			//from start to shared
			float vecAB[2] = {shared->x()-start->x(),
							 shared->y()-start->y()};
			float magAB = hypot(vecAB[0], vecAB[1]);

			//from shared to end
			float vecBC[2] = {end->x()-shared->x(),
							 end->y()-shared->y()};
			float magBC = hypot(vecBC[0], vecBC[1]);

			if (((vecAB[0]/magAB + vecBC[0]/magBC) == 0) &&
				((vecAB[1]/magAB + vecBC[1]/magBC) == 0)) return true;
		}
		return false;
	}

	float t, u;
	if (det2 != 0 && det4 != 0) {
		t = det1/det2;
		u = det3/det4;
		if (t > 0 && t < 1 &&
			u > 0 && u < 1) { //changing >=/<= to >/< might not be a definitive check to see if the segments intersect at a vertex
			return true;
		}
	}

	//If det2 and det4 are 0, then the lines are either
	//parallel or coincident
	//convert segments into slope-intercept form and see if the intercepts are the same
	//if intercepts are the same, check bounding boxes
	//Swap 1b and 2b and recalculate the dets; if they
	//are still 0, then check bounding boxes
	//Swap (x2, y2) and (x4, y4)
	//note: there is 1 fringe case where this may not work, but for the most part it should be fine
	det2 = (x1-x4)*(y3-y2) - (y1-y4)*(x3-x2);
	if (det2 == 0) {
		//If the first segment lies outside the bounding box of the second, then
		//they aren't crossing
		if (((x1 < x3) && (x2 < x3) && (x1 < x4) && (x2 < x4)) ||
			((x1 > x3) && (x2 > x3) && (x1 > x4) && (x2 > x4)) ||
			((y1 < y3) && (y2 < y3) && (y1 < y4) && (y2 < y4)) ||
			((y1 > y3) && (y2 > y3) && (y1 > y4) && (y2 > y4))) return false;

		return true;
	}
	return false;
}

Vertex* findSharedVertex(Vertex* edge1a, Vertex* edge1b, Vertex* edge2a, Vertex* edge2b)
{
	if (edge1a == edge2a || edge1a == edge2b) return edge1a;
	if (edge1b == edge2a || edge1b == edge2b) return edge1b;
	return nullptr;
}

void color(Vertex* v1, Vertex* v2)
{
	//Putting 2 just in case, there should only
	//be 1 vertex in common however
	std::vector<Vertex*> common(2);
	set_intersection(v1->partners.begin(), v1->partners.end(), v2->partners.begin(), v2->partners.end(), common.begin(), y_compare);
	Vertex* v3 = common[0];

	if (v1->color + v2->color + v3->color == 6) return;


	if (v2->color == 0) {
		if (v3->color == 0) {
			v2->color = (v1->color%3) + 1;
			v3->color = 6 - v1->color - v2->color;
		} else
			v2->color = 6 - v1->color - v3->color;
	} else {
		v3->color = 6 - v1->color - v2->color;
	}

	//we could technically put a recursive case here
}

//both vertices must be colored, and both must share an edge
void colorRec(Vertex* v1, Vertex* v2)
{
	std::vector<Vertex*> common(2); //2 connected vertices have at most 2 common vertices
	set_intersection(v1->partners.begin(), v1->partners.end(), v2->partners.begin(), v2->partners.end(), common.begin(), y_compare);

	//if common isn't empty, although this shouldn't need to be checked
	bool allColored = true;
	for (auto& v : common) {
		if (v == nullptr) break; //if there is only 1 common vertex
		if (v->color == 0) {
			allColored = false;
			break;
		}
	}
	if (allColored) return;


	for (auto& v : common) {
		if (v == nullptr) break; //if there is only 1 common vertex
		if (v->color == 0) {
			v->color = 6 - v1->color - v2->color;
			colorRec(v, v1);
			colorRec(v, v2);
		}
	}
}


int smallestColor(int r, int g, int b)
{
	int min = r;
	if (g < min) min = g;
	if (b < min) min = b;

	if (min == r) return 1;
	if (min == g) return 2;
	if (min == b) return 3;

	//Function should never get to this point,
	//putting this to get rid of the warnings
	return 0;
}

bool y_compare(Vertex* v1, Vertex* v2) {
	if (v1->y() == v2->y())
		//Higher x-values go first because the lowest x-value will mark
		//the end of an edge, and should always be processed last
		return (v1->x() > v2->x());
	return (v1->y() > v2->y());
}


bool DCEL_y_compare(DCELVertex* v1, DCELVertex* v2) {
	if (v1->parent()->y() == v2->parent()->y())
		//This is special because when triangulating, we need the lower
		//x-value to be first
		return (v1->parent()->x() < v2->parent()->x());
	return (v1->parent()->y() > v2->parent()->y());
}
