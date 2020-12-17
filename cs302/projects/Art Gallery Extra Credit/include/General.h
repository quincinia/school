#ifndef GENERAL_H
#define GENERAL_H
#include "dcel.h"
#include <vector>
#include <algorithm>

/**
 * @brief setClockwise
 * Will align all vertices in the mesh such that their "next" pointers
 * will point clockwise around the polygon (if they are not already).
 *
 * Finds the highest vertex from a set. Then compares that vertex's neighbors
 * to see which one points "more to the right". (its unit vector has a greater x-component)
 * @param input
 */
void setClockwise(std::vector<Vertex*> input);

/**
 * @brief crossProduct
 * Calculates (prev->mid) x (mid->next)
 * Because these are 2d vectors, we only need to calculate the third value
 * @param prev
 * @param mid
 * @param next
 * @return
 * Negative value is a right hand turn; positive a left hand turn
 * (see Face::createsExteriorEdge())
 */
float crossProduct(Vertex* prev, Vertex* mid, Vertex* next);

/**
 * @brief classifyVertices
 * Will classify vertices based on their y-coordinate relation to its
 * neighbors and where the interior of the polygon is relative to that vertex.
 * @param input
 */
void classifyVertices(std::vector<Vertex*> input); //obsolete
void cV2(std::vector<Vertex*> input); //updated version of the above

/**
 * @brief y_compare
 * Compares heights. If equal, compares x-coordinates.
 * @param v1
 * @param v2
 * @return
 */
bool y_compare(Vertex* v1, Vertex* v2);
bool DCEL_y_compare(DCELVertex* v1, DCELVertex* v2);

/**
 * @brief makeMonotone
 * Goes through all vertices of mesh and creates diagonals
 * so as to partition the mesh into y-monotone pieces
 */
void makeMonotone(Mesh& polygon);

/**
 * @brief segmentsIntersect
 * see https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection for algorithm
 * @param edge1a
 * @param edge1b
 * @param edge2a
 * @param edge2b
 * @return
 */
bool segmentsIntersect(Vertex* edge1a, Vertex* edge1b, Vertex* edge2a, Vertex* edge2b);

//Helper to segmentsIntersect, returns which 2 of the 4 are the same
Vertex* findSharedVertex(Vertex* edge1a, Vertex* edge1b, Vertex* edge2a, Vertex* edge2b);


/**
 * @brief color
 * Prereqs: v1 must be colored, v1 and v2 must be neighbors of each other
 * Finds the mutual vertex between v1 and v2 (in a triangulated polygon, two consecutive
 * vertices will always have 1 (and only 1) common vertex they share a diagonal with)
 * Adds color to v2 and the mutual vertex (if they aren't already colored)
 * @param v1
 * @param v2
 */
void color(Vertex* v1, Vertex* v2); //obsolete
void colorRec(Vertex* v1, Vertex* v2);

/**
 * @brief smallestColor
 * Determines the smallest value of the r/g/b counts
 * @param r
 * @param g
 * @param b
 * @return
 * Returns the colorID of the smallest color (r = 1, g = 2, b = 3)
 */
int smallestColor(int r, int g, int b);
#endif // GENERAL_H
