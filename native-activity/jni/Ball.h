/*
 * Ball.h
 *
 *  Created on: 17 Nis 2013
 *      Author: Engin Manap
 */

#ifndef BALL_H_
#define BALL_H_

#include <string>
#include <vector>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <algorithm>
#include <android/log.h>
#include  <math.h>
#include "glslHelper.h"

extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
extern PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;

#define PI 3.14159265

namespace androng {

class Ball {

private:
	float fXOffset;
	float fYOffset;
	float* vertexPositionsPointer;
	int elementPerVertex;

	int elementsOrderSize;

	int vertexPositionsSize;
	GLuint _ballGLSLProgram;
	GLuint positionBufferObject;
	GLuint positionBufferPointer;
	GLuint perspectiveMatrixLocation;
	GLuint offsetLocation;
	GLuint vertexArrayObject;

	GLuint elementOrderBuffer;
	unsigned int* elementsOrderPointer;

	std::string VSbasic;
	std::string FSbasic;

	float perspectiveMatrix[16];

	void initializeVertexShader();
	void initializeFragmentShader();
	void initializeVertexPositions();
	void initializeElementArray();
	void initializeVertexArrayObject();
	void initializePerspectiveMatrix(int, int);
	void initializeProgram();
	void initializeVertexBuffer();
public:
	Ball(int, int);
	void draw(float, float);
	void draw2(float, float);
};

}

#endif /* BALL_H_ */
