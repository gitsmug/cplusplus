#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include "shapeData.h"

class ShapeGenerator
{
private:
	static ShapeData MakePlaneVerts(uint dimensions);
	static ShapeData MakePlaneIndices(uint dimensions);
	static ShapeData makePlaneUnseamedIndices(uint tesselation);

	// Teapot helpers
	static void generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid);
	static void moveLid(int grid, float *v, glm::mat4 lidTransform);
	static void buildPatchReflect(int patchNum,
		float *B, float *dB,
		float *v, float *n,
		float *tc, unsigned short *el,
		int &index, int &elIndex, int &tcIndex, int grid,
		bool reflectX, bool reflectY);
	static void buildPatch(glm::vec3 patch[][4],
		float *B, float *dB,
		float *v, float *n, float *tc,
		unsigned short *el,
		int &index, int &elIndex, int &tcIndex,
		int grid, glm::mat3 reflect,
		bool invertNormal);
	static void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);
	static void computeBasisFunctions(float * B, float * dB, int grid);
	static glm::vec3 evaluate(int gridU, int gridV, float *B, glm::vec3 patch[][4]);
	static glm::vec3 evaluateNormal(int gridU, int gridV,
		float *B, float *dB, glm::vec3 patch[][4]);
public:
	static ShapeData MakeTriangle();
	static ShapeData MakeCube();
	static ShapeData MakeArrow();
	static ShapeData MakePlane(uint dimensions = 10);
	static ShapeData makeTeapot(uint tesselation = 10, const glm::mat4& lidTransform = glm::mat4(1.0f));
	static ShapeData makeSphere(uint tesselation = 20);
	static ShapeData makeTorus(uint tesselation = 20);
	static ShapeData generateNormals(const ShapeData& data);
};

#endif