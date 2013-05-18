/*
 * RacketBar.cpp
 *
 *  Created on: 28 Mar 2013
 *      Author: Engin Manap
 */

#include "RacketBar.h"

namespace androng {
/*
 void RacketBar::initializeVertexShader() {
 VSbasic = "attribute vec4 vPosition;\n"
 "uniform vec2 offset;"
 "void main()\n"
 "{\n"
 "vec4 totalOffset = vec4(offset.x, offset.y, 0.0, 0.0);\n"
 " gl_Position = vPosition + totalOffset;\n"
 "}\n";

 }
 */
void RacketBar::initializeVertexShader() {
	VSRacketbarbasic =

			"attribute vec4 vPosition;\n"
			"attribute mediump vec4 vColor;\n"
			"varying mediump vec4 outputColor;\n"
			"uniform mat4 perspectiveMatrix;\n"
			"uniform vec2 offset;\n"
			"\n"
			"void main()\n"
			"{\n"
			"vec4 cameraPos = vPosition + vec4(offset.x, offset.y, 0.0, 0.0);\n"
			"outputColor = vColor;"
			"gl_Position = perspectiveMatrix * cameraPos;\n"
			"}\n";
}

void RacketBar::initializeFragmentShader() {
	FSRacketbarbasic =
			"varying mediump vec4 outputColor;\n"
			"\n"
			"void main() {\n"
				//"gl_FragColor = vec4 ( 0.8, 0.0, 0.0, 1.0 ) + outputColor;\n"
				"gl_FragColor = outputColor;\n"
			"}\n";
}

void RacketBar::initializeVertexPositions() {
	float incomingVertexes[] = {
			-0.5f,  0.05f, -1.05f, // A
			 0.5f,  0.05f, -1.05f, // B
			-0.5f, -0.05f, -1.05f, // C
			 0.5f, -0.05f, -1.05f, // D
			-0.5f,  0.05f, -1.25f, // E
			 0.5f,  0.05f, -1.25f, // F
			-0.5f, -0.05f, -1.25f, // G
			 0.5f, -0.05f, -1.25f, // H
			-0.5f,  0.05f, -1.05f, // A
			 0.5f,  0.05f, -1.05f, // B
			-0.5f, -0.05f, -1.05f, // C
			 0.5f, -0.05f, -1.05f, // D
			-0.5f,  0.05f, -1.25f, // E
			 0.5f,  0.05f, -1.25f, // F
			-0.5f, -0.05f, -1.25f, // G
			 0.5f, -0.05f, -1.25f, // H
			-0.5f,  0.05f, -1.05f, // A
			 0.5f,  0.05f, -1.05f, // B
			-0.5f, -0.05f, -1.05f, // C
			 0.5f, -0.05f, -1.05f, // D
			-0.5f,  0.05f, -1.25f, // E
			 0.5f,  0.05f, -1.25f, // F
			-0.5f, -0.05f, -1.25f, // G
			 0.5f, -0.05f, -1.25f, // H

			1.0, 0.0, 0.0, 0.0, // A
			1.0, 0.0, 0.0, 0.0, // B
			1.0, 0.0, 0.0, 0.0, // C
			1.0, 0.0, 0.0, 0.0, // D
			1.0, 0.0, 0.0, 0.0, // E
			1.0, 0.0, 0.0, 0.0, // F
			1.0, 0.0, 0.0, 0.0, // G
			1.0, 0.0, 0.0, 0.0, // H
			0.0, 1.0, 0.0, 0.0, // A //start
			0.0, 1.0, 0.0, 0.0, // B
			0.0, 1.0, 0.0, 0.0, // C
			0.0, 1.0, 0.0, 0.0, // D
			0.0, 1.0, 0.0, 0.0, // E
			0.0, 1.0, 0.0, 0.0, // F
			0.0, 1.0, 0.0, 0.0, // G
			0.0, 1.0, 0.0, 0.0, // H
			0.0, 0.0, 1.0, 0.0, // A //start
			0.0, 0.0, 1.0, 0.0, // B
			0.0, 0.0, 1.0, 0.0, // C
			0.0, 0.0, 1.0, 0.0, // D
			0.0, 0.0, 1.0, 0.0, // E
			0.0, 0.0, 1.0, 0.0, // F
			0.0, 0.0, 1.0, 0.0, // G
			0.0, 0.0, 1.0, 0.0, // H


			};

	elementPerVertex = 7;
	vertexPositionsSize = sizeof(incomingVertexes);
	vertexPositionsPointer = (float*) malloc(vertexPositionsSize);
	memcpy(vertexPositionsPointer, incomingVertexes, vertexPositionsSize);
	vertexPositionsCount = vertexPositionsSize / sizeof(float);

}

void RacketBar::initializeElementArray() {
	unsigned int incomingElements[] = {
			20,22,21,
			21,22,23,
			10,11,14,
			11,14,15,
			0,4,6,
			0,2,6,
			1,3,5,
			3,5,7,
			8,9,13,
			8,13,12,
			16,17,18,
			17,18,19,

	};

	elementsOrderSize = sizeof(incomingElements);
	elementsOrderPointer = (unsigned int*) malloc(elementsOrderSize);
	memcpy(elementsOrderPointer, incomingElements, elementsOrderSize);
}

GLuint RacketBar::CreateShader(GLenum eShaderType,
		const std::string &strShaderFile) {
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType) {
		case GL_VERTEX_SHADER:
			strShaderType = "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "fragment";
			break;
		}

		/*fprintf(stderr, "Compile failure in %s shader:\n%s\n",
		 strShaderType, strInfoLog);
		 */
		LOGI("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

GLuint RacketBar::CreateProgram(const std::vector<GLuint> &shaderList) {
	GLuint racketGLSLProgram = glCreateProgram();

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(racketGLSLProgram, shaderList[iLoop]);
	glLinkProgram(racketGLSLProgram);

	GLint status;
	glGetProgramiv(racketGLSLProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(racketGLSLProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(racketGLSLProgram, infoLogLength, NULL, strInfoLog);
		//fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		LOGI("Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(racketGLSLProgram, shaderList[iLoop]);

	return racketGLSLProgram;
}

void RacketBar::initializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER,this-> VSRacketbarbasic));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, this->FSRacketbarbasic));

	_racketbarGLSLProgram = CreateProgram(shaderList);

	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

void RacketBar::initializeVertexBuffer() {
	glGenBuffers(1, &vertexPositionsBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexPositionsSize,
			vertexPositionsPointer, GL_STATIC_DRAW);

	glGenBuffers(1, &elementOrderBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementOrderBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,elementsOrderSize,
			elementsOrderPointer, GL_STATIC_DRAW);
}

void RacketBar::initializePerspectiveMatrix(int height, int width){
	float fxFrustumScale = 1.0f;
	float fyFrustumScale = 1.0f;
	float fzNear = 0.5f;
	float fzFar = 3.0f;

	if(height > width){
		//x is bigger, so we will scale x.
		fxFrustumScale = (float)height / (float)width;
	} else {
		//y is bigger, scale y
		fyFrustumScale = (float)width / (float)height;

	}

	memset(perspectiveMatrix, 0, sizeof(perspectiveMatrix)); //set 0 to all elements.
	perspectiveMatrix[0] = fxFrustumScale;
	perspectiveMatrix[5] = fyFrustumScale;
	perspectiveMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
	perspectiveMatrix[11] = -1.0f;
	perspectiveMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);

}


void RacketBar::initializeVertexArrayObject(){
	positionBufferPointer = glGetAttribLocation(_racketbarGLSLProgram,
			"vPosition");

	colorInputPointer = glGetAttribLocation(_racketbarGLSLProgram, "vColor");

	glGenVertexArraysOES(1, &vertexArrayObject);
	glBindVertexArrayOES(vertexArrayObject);


	int colorDataOffset = vertexPositionsSize / elementPerVertex * 3;

	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementOrderBuffer);

	glVertexAttribPointer(positionBufferPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionBufferPointer);

	glVertexAttribPointer(colorInputPointer, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glEnableVertexAttribArray(colorInputPointer);

	glBindVertexArrayOES(0);
	glDisableVertexAttribArray(positionBufferPointer);
	glDisableVertexAttribArray(colorInputPointer);
}


RacketBar::RacketBar(bool userBar, int height, int width) {
	if (userBar) {
		fYOffset = -0.8f;
	} else {
		fYOffset = 0.8f;
	}
	isUserBar = userBar;
	initializeVertexShader();
	initializeFragmentShader();
	initializeProgram();
	initializeVertexPositions();
	initializeElementArray();
	initializeVertexBuffer();
	initializePerspectiveMatrix(height, width);
	initializeVertexArrayObject();

	offsetLocation = glGetUniformLocation(_racketbarGLSLProgram,
			"offset");
	perspectiveMatrixLocation = glGetUniformLocation(
			_racketbarGLSLProgram, "perspectiveMatrix");

	//positionBufferPointer = glGetAttribLocation(_racketbarGLSLProgram, "vPosition");
	//colorInputPointer = glGetAttribLocation(_racketbarGLSLProgram, "vColor");
}

void RacketBar::draw(float position) {

	glUseProgram(_racketbarGLSLProgram);

	glUniform2f(offsetLocation, position, fYOffset);
	glUniformMatrix4fv(perspectiveMatrixLocation, 1, GL_FALSE,
			perspectiveMatrix);

	glBindVertexArrayOES(vertexArrayObject);

	glDrawElements(GL_TRIANGLES, elementsOrderSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	glBindVertexArrayOES(0);

	glUseProgram(0);
}

void RacketBar::draw2(float position) {


	glUseProgram(_racketbarGLSLProgram);

	glUniform2f(offsetLocation, position, fYOffset);
	glUniformMatrix4fv(perspectiveMatrixLocation, 1, GL_FALSE, perspectiveMatrix);

	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer);
	glEnableVertexAttribArray(positionBufferPointer);
	glEnableVertexAttribArray(colorInputPointer);

	glVertexAttribPointer(positionBufferPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	int startPoint = vertexPositionsSize / elementPerVertex * 3;
	glVertexAttribPointer(colorInputPointer, 4, GL_FLOAT, GL_FALSE, 0, (void *)(startPoint));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementOrderBuffer);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexPositionsSize / elementPerVertex);

	glDrawElements(GL_TRIANGLES, elementsOrderSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(colorInputPointer);
	glDisableVertexAttribArray(positionBufferPointer);

	glUseProgram(0);
}

}
