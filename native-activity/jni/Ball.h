/*
 * Ball.h
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
#include  <math.h>

#ifndef BALL_H_
#define BALL_H_

#define PI 3.14159265

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

namespace androng {

class Ball {

private:
	float fXOffset;
	float fYOffset;
	float* vertexPositionsPointer;
	int elementPerVertex;

	int vertexPositionsSize;
	GLuint _ballGLSLProgram;
	GLuint positionBufferObject;
	GLuint positionBufferPointer;
	GLuint perspectiveMatrixLocation;
	GLuint offsetLocation;

	std::string VSbasic;
	std::string FSbasic;

	float perspectiveMatrix[16];

	void initializeVertexShader();
	void initializeFragmentShader();
	void initializeVertexPositions();
	void initializePerspectiveMatrix(int, int);
	GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);
	void initializeProgram();
	void initializeVertexBuffer();
public:
	Ball(int, int);
	void draw(float, float);
};

}

#endif /* BALL_H_ */
