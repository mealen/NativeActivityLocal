/*
 * RacketBar.h
 *
 *  Created on: 17 Nis 2013
 *      Author: Engin Manap
 */

#include <string>
#include <vector>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <algorithm>
#include <android/log.h>
#include "glslHelper.h"

#ifndef RACKETBAR_H_
#define RACKETBAR_H_

extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
extern PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;

namespace androng {

class RacketBar {

private:
	bool isUserBar;
	float fYOffset;
	float* vertexPositionsPointer;
	unsigned int* elementsOrderPointer;
	int vertexPositionsSize;
	int vertexPositionsCount;
	int elementsOrderSize;
	int elementPerVertex;
	float perspectiveMatrix[16];
	GLuint _racketbarGLSLProgram;
	GLuint vertexPositionsBuffer;
	GLuint elementOrderBuffer;
	GLuint positionBufferPointer;
	GLuint colorInputPointer;

	GLuint vertexArrayObject;

	GLuint perspectiveMatrixLocation;
	GLuint offsetLocation;

	std::string VSRacketbarbasic;
	std::string FSRacketbarbasic;
	void initializeVertexShader();
	void initializeFragmentShader();
	void initializeVertexPositions();
	void initializeElementArray();
	void initializePerspectiveMatrix(int, int);

	void initializeProgram();
	void initializeVertexBuffer();
	void initializeVertexArrayObject();

public:
	RacketBar(bool, int, int);
	void draw(float);
	void draw2(float);

};
}


#endif /* RACKETBAR_H_ */
