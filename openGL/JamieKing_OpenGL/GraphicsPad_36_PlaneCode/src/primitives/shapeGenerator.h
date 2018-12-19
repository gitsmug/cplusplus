#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include "shapeData.h"

class ShapeGenerator
{
private:
	static ShapeData MakePlaneVerts(uint dimensions);
	static ShapeData MakePlaneIndices(uint dimensions);
public:
	static ShapeData MakeTriangle();
	static ShapeData MakeCube();
	static ShapeData MakeArrow();
	static ShapeData MakePlane(uint dimensions = 10);
};

#endif