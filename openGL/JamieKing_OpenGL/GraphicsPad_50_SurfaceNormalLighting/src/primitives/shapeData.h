#ifndef SHAPEDATA_H
#define SHAPEDATA_H

// include OpenGL
#ifdef __WXMAC__
#include <OpenGL/glew.h>
#else
#include <GL/glew.h>
#endif

#include "vertex.h"

struct ShapeData
{
	ShapeData() :
		vertices(0),
		numVertices(0),
		indices(0),
		numIndices(0)
	{}

	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}

	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}

	void CleanUp()
	{
		delete [] vertices;
		delete [] indices;

		vertices = 0;
		indices = 0;

		numVertices = 0;
		numIndices = 0;
	}
};

#endif