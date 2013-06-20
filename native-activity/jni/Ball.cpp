/*
 * Ball.cpp
 *
 *  Created on: 28 Mar 2013
 *      Author: Engin Manap
 */


#include "Ball.h"


#define PI 3.14159265

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

namespace androng {

	void Ball::initializeVertexShader() {
		VSbasic =
				"attribute vec4 vPosition;\n"
				"uniform vec2 offset;\n"
				"uniform mat4 perspectiveMatrix;\n"
				"varying mediump vec4 outputColor;\n"
				"void main()\n"
				"{\n"
				"outputColor = vec4( 0.5, 0.5, 0.5, 1.0 );"
				"vec4 lastPosition = vPosition + vec4(offset.x, offset.y, 0.0, 0.0);\n"
				"gl_Position = perspectiveMatrix * lastPosition;\n"
				"}\n";

	}

	void Ball::initializeFragmentShader() {
		FSbasic =
				"precision mediump float;\n"
				"varying mediump vec4 outputColor;\n"
				// "uniform vec4 vColor;\n"
				"void main() {\n"
					//"vec4 originalColor = vec4 ( 0.5, 0.5, 0.5, 1.0 );\n"
					"gl_FragColor = outputColor;\n"
				"}\n";
	}

	void Ball::initializeVertexPositions() {
		float ballRadius = 0.1;
		int ballVertexCount = 16;
		float ballElementAngle = 3.14159265 / ballVertexCount;

		LOGI("ball angle = %f", ballElementAngle);


		elementPerVertex = 3;
		vertexPositionsSize = sizeof(float) * elementPerVertex * (ballVertexCount + 2); //+1 for center vertex, +1 for start and stop gets to be the same

		vertexPositionsPointer = (float*) malloc(vertexPositionsSize);
		vertexPositionsSize = vertexPositionsSize / sizeof(float);

		*vertexPositionsPointer = 0.0f;
		*(vertexPositionsPointer + 1) = 0.0f;
		*(vertexPositionsPointer + 2) = -1.15;
		for(int i=1;i <= ballVertexCount;i++){
			*(vertexPositionsPointer + (elementPerVertex * i)    ) = sin(ballElementAngle * 2 * i) * ballRadius;
			*(vertexPositionsPointer + (elementPerVertex * i) + 1) = cos(ballElementAngle * 2 * i) * ballRadius;
			*(vertexPositionsPointer + (elementPerVertex * i) + 2) = -1.10;
		}
		*(vertexPositionsPointer + (elementPerVertex * (ballVertexCount+1))  ) = sin(ballElementAngle * 2 * (ballVertexCount+1)) * ballRadius;
		*(vertexPositionsPointer + (elementPerVertex * (ballVertexCount+1))+1) = cos(ballElementAngle * 2 * (ballVertexCount+1)) * ballRadius;
		*(vertexPositionsPointer + (elementPerVertex * (ballVertexCount+1))+2) = -1.10;

	}


	void Ball::initializeElementArray() {
		unsigned int incomingElements[] = {
					0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17

		};

		elementsOrderSize = sizeof(incomingElements);
		elementsOrderPointer = (unsigned int*) malloc(elementsOrderSize);
		memcpy(elementsOrderPointer, incomingElements, elementsOrderSize);
	}

	void Ball::initializeProgram() {
		std::vector<GLuint> shaderList;

		shaderList.push_back(GLSLHelper::CreateShader(GL_VERTEX_SHADER, this->VSbasic));
		shaderList.push_back(GLSLHelper::CreateShader(GL_FRAGMENT_SHADER, this->FSbasic));

		_ballGLSLProgram = GLSLHelper::CreateProgram(shaderList);

		positionBufferPointer = glGetAttribLocation(_ballGLSLProgram, "vPosition");
		perspectiveMatrixLocation = glGetUniformLocation(_ballGLSLProgram, "perspectiveMatrix");
		offsetLocation = glGetUniformLocation(_ballGLSLProgram, "offset");

		glUseProgram(_ballGLSLProgram);
		glUniformMatrix4fv(perspectiveMatrixLocation, 1, GL_FALSE, perspectiveMatrix);
		glUseProgram(0);

		std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
	}

	void Ball::initializeVertexBuffer() {
		glGenBuffers(1, &positionBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glBufferData(GL_ARRAY_BUFFER, vertexPositionsSize * sizeof(float),
				vertexPositionsPointer, GL_STATIC_DRAW);

		glGenBuffers(1, &elementOrderBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementOrderBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,elementsOrderSize,
				elementsOrderPointer, GL_STATIC_DRAW);
	}

	void Ball::initializeVertexArrayObject(){
		glGenVertexArraysOES(1, &vertexArrayObject);
		glBindVertexArrayOES(vertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementOrderBuffer);

		glVertexAttribPointer(positionBufferPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(positionBufferPointer);

		glBindVertexArrayOES(0);

	}

	void Ball::initializePerspectiveMatrix(int height, int width){
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




	Ball::Ball(int height, int width) {
		fXOffset = 0.0f;
		fYOffset = 0.0f;

		initializeVertexShader();
		initializeFragmentShader();
		initializePerspectiveMatrix(height,width);
		initializeProgram();
		initializeVertexPositions();
		initializeElementArray();
		initializeVertexBuffer();

		initializeVertexArrayObject();
	}

	void Ball::draw(float xPosition, float yPosition) {
		glUseProgram(_ballGLSLProgram);

		glBindVertexArrayOES(vertexArrayObject);
		glUniform2f(offsetLocation, xPosition, yPosition);
		glDrawElements(GL_TRIANGLE_FAN, elementsOrderSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glBindVertexArrayOES(0);

		glUseProgram(0);
	}

	void Ball::draw2(float xPosition, float yPosition) {

		glUseProgram(_ballGLSLProgram);

		glUniform2f(offsetLocation, xPosition, yPosition);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glEnableVertexAttribArray(positionBufferPointer);
		glVertexAttribPointer(positionBufferPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLE_FAN, 0,vertexPositionsSize / elementPerVertex);

		glDisableVertexAttribArray(positionBufferPointer);

		glUseProgram(0);
	}

}
