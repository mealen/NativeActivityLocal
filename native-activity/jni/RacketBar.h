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

#ifndef RACKETBAR_H_
#define RACKETBAR_H_

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

namespace androng {

class RacketBar {

private:
	bool isUserBar;
	float fYOffset;
	float* vertexPositionsPointer;
	int vertexPositionsSize;
	int elementPerVertex;
	float perspectiveMatrix[16];
	GLuint _racketbarGLSLProgram;
	GLuint positionBufferObject;
	GLuint positionBufferPointer;
	GLuint colorInputPointer;

	std::string VSRacketbarbasic;
	std::string FSRacketbarbasic;
	void initializeVertexShader();
	void initializeFragmentShader();
	void initializeVertexPositions();
	void initializePerspectiveMatrix();
	GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);
	void initializeProgram();
	void initializeVertexBuffer();

public:
	RacketBar(bool);
	void draw(float);

};
}


#endif /* RACKETBAR_H_ */
