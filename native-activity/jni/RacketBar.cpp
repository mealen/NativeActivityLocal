/*
 * RacketBar.cpp
 *
 *  Created on: 28 Mar 2013
 *      Author: Engin Manap
 */

#include "RacketBar.h"

namespace androng {

void RacketBar::initializeVertexShader() {
	VSRacketbarbasic =
			"attribute vec4 vPosition;\n"
			"attribute mediump vec4 vColor;\n"
			"uniform vec2 offset;\n"
			"uniform mat4 perspectiveMatrix;\n"
			"varying mediump vec4 outputColor;\n"
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
			"precision mediump float;\n"
			"varying mediump vec4 outputColor;\n"
			"\n"
			"void main() {\n"
				//"gl_FragColor = vec4 ( 0.8, 0.0, 0.0, 1.0 ) + outputColor;\n"
				"gl_FragColor = outputColor;\n"
			"}\n";
}

void RacketBar::initializeVertexPositions() {
	float incomingVertexes[] = {
			-0.25f,  0.05f, -1.05f, // A
			 0.25f,  0.05f, -1.05f, // B
			-0.25f, -0.05f, -1.05f, // C
			 0.25f, -0.05f, -1.05f, // D
			-0.25f,  0.05f, -1.15f, // E
			 0.25f,  0.05f, -1.15f, // F
			-0.25f, -0.05f, -1.15f, // G
			 0.25f, -0.05f, -1.15f, // H
			-0.25f,  0.05f, -1.05f, // A
			 0.25f,  0.05f, -1.05f, // B
			-0.25f, -0.05f, -1.05f, // C
			 0.25f, -0.05f, -1.05f, // D
			-0.25f,  0.05f, -1.15f, // E
			 0.25f,  0.05f, -1.15f, // F
			-0.25f, -0.05f, -1.15f, // G
			 0.25f, -0.05f, -1.15f, // H
			-0.25f,  0.05f, -1.05f, // A
			 0.25f,  0.05f, -1.05f, // B
			-0.25f, -0.05f, -1.05f, // C
			 0.25f, -0.05f, -1.05f, // D
			-0.25f,  0.05f, -1.15f, // E
			 0.25f,  0.05f, -1.15f, // F
			-0.25f, -0.05f, -1.15f, // G
			 0.25f, -0.05f, -1.15f, // H

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



void RacketBar::initializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(GLSLHelper::CreateShader(GL_VERTEX_SHADER,this-> VSRacketbarbasic));
	shaderList.push_back(GLSLHelper::CreateShader(GL_FRAGMENT_SHADER, this->FSRacketbarbasic));

	_racketbarGLSLProgram = GLSLHelper::CreateProgram(shaderList);

	positionBufferPointer = glGetAttribLocation(_racketbarGLSLProgram, "vPosition");
	colorInputPointer = glGetAttribLocation(_racketbarGLSLProgram, "vColor");
	offsetLocation = glGetUniformLocation(_racketbarGLSLProgram, "offset");
	perspectiveMatrixLocation = glGetUniformLocation(_racketbarGLSLProgram, "perspectiveMatrix");

	glUseProgram(_racketbarGLSLProgram);
	glUniformMatrix4fv(perspectiveMatrixLocation, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(0);

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
	glGenVertexArraysOES(1, &vertexArrayObject);
	glBindVertexArrayOES(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementOrderBuffer);

	int colorDataOffset = vertexPositionsSize / elementPerVertex * 3;

	glVertexAttribPointer(positionBufferPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionBufferPointer);

	glVertexAttribPointer(colorInputPointer, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glEnableVertexAttribArray(colorInputPointer);

	glBindVertexArrayOES(0);
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
	initializePerspectiveMatrix(height, width);
	initializeProgram();
	initializeVertexPositions();
	initializeElementArray();
	initializeVertexBuffer();

	initializeVertexArrayObject();
}

void RacketBar::draw(float position) {
	glUseProgram(_racketbarGLSLProgram);

	glBindVertexArrayOES(vertexArrayObject);
	glUniform2f(offsetLocation, position, fYOffset);

	glDrawElements(GL_TRIANGLES, elementsOrderSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR){
		LOGE("gl error");
	}

	glBindVertexArrayOES(0);

	glUseProgram(0);


}

void RacketBar::draw2(float position) {

	glUseProgram(_racketbarGLSLProgram);

	glUniform2f(offsetLocation, position, fYOffset);

	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionsBuffer);
	glEnableVertexAttribArray(positionBufferPointer);
	glEnableVertexAttribArray(colorInputPointer);

	glVertexAttribPointer(positionBufferPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	int startPoint = vertexPositionsSize / elementPerVertex * 3;
	glVertexAttribPointer(colorInputPointer, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(startPoint));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementOrderBuffer);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexPositionsSize / elementPerVertex);

	glDrawElements(GL_TRIANGLES, elementsOrderSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(colorInputPointer);
	glDisableVertexAttribArray(positionBufferPointer);

	glUseProgram(0);
}

}
