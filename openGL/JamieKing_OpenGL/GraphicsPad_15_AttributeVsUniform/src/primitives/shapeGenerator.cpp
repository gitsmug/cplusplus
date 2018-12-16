#include "shapeGenerator.h"
#include <glm/glm.hpp>
#include "vertex.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

ShapeData ShapeGenerator::MakeTriangle()
{
	ShapeData shapeData;

	Vertex myTri[] =
	{
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),

		glm::vec3(-1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
	};

	shapeData.numVertices = NUM_ARRAY_ELEMENTS(myTri);
	shapeData.vertices = new Vertex[shapeData.numVertices];
	memcpy(shapeData.vertices, myTri, sizeof(myTri));

	GLushort indices[] = { 0, 1, 2 };
	shapeData.numIndices = NUM_ARRAY_ELEMENTS(indices);
	shapeData.indices = new GLushort[shapeData.numIndices];
	memcpy(shapeData.indices, indices, sizeof(indices));

	return shapeData;
}