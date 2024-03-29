/************************************************************************
     File:        Edge.h

     Author:     
                  Stephen Chenney, schenney@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu

     Comment:    
						(c) 2001-2002 Stephen Chenney, University of Wisconsin at Madison
						Class header file for Edge class. Stores data about edges in the maze.
		

     Platform:    Visio Studio.Net 2003 (converted to 2005)

*************************************************************************/
#ifndef _EDGE_H_
#define _EDGE_H_

#include "Vertex.h"
#include <qline.h>
#include <vector>
#include <windows.h>
#include <gl\gl.h>
#include <gl\GLU.h>
#include "Vec3D.h"
#include "Vec4D.h"

using std::vector;

class Edge {

public:

	// Constructor takes the index, pointers to the start and end
	// vertices, and r, g and b for the color.
	Edge(int, Vec3D, Vec3D, Vec3D, Vec3D, float, float, float, bool);
	Edge(vector<Vec3D>);
	Edge(Vec3D, Vec3D, Vec3D);
public:
	static void AddIfNotExist(vector<Vec3D>& list, const Vec3D& element);
	static bool IsLeft(const Edge&, const Vec3D&);
	static bool IsSameSide(const Edge&, const Vec3D&, const Vec3D&);
	static Vec3D Mirror(const Edge&, const Vec3D&);

	QLineF::IntersectType Intersect(const Vec3D&, const Vec3D&, Vec3D&);

	// Add a cell to the neighbors of this edge. Valid values for
	// which_one are Edge::LEFT or Edge::RIGHT.
	void Add_Cell(class Cell *cell, const char which_one){ 
		neighbors[which_one] = cell; 
	};

	// Given a cell, return the neighboring cell across this edge.
	// This is very useful.
	class Cell*	Neighbor(class Cell *cell) { 
		return cell == neighbors[LEFT] ? neighbors[RIGHT] : neighbors[LEFT]; 
	};

	void Draw(const vector<Vec3D>& boundary, Edge* mirrorPlane, bool onlyEdge = false);
	bool Clip(const Vec3D& o, const vector<Vec3D>& boundary, const Vec3D& center, vector<Vec3D>& newBoundary, bool clipTop);
	void LeftToRight(vector<Vec3D>& boundary);
public:
	// Constants.
	// To access these outside the edge class, use Edge::LEFT etc.
	static const char LEFT;
	static const char RIGHT;

	static double wallHeight;
	static double thickness;

	int index;				// An identifier

	class Cell* neighbors[2];	// The cells that this edge lies
    										// between, indexed by Edge::LEFT and
											// Edge::RIGHT. One or the other may
											// be 0 if the edge is on the
											// boundary of the maze

	vector<Vec3D> edgeBoundary;

	bool isFloor = false;
	bool isCeiling = false;
    bool opaque;	// True is this edge cannot be seen or
    						// walked through, false otherwise.

    float color[3]; // The color for this edge / wall.
	int endpointId[2];
	double max_x, max_y, min_x, min_y;

	Edge* mirror = nullptr;
};

#endif

