/*
 * openglHelper.cpp
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
			"attribute vec4 vColor;\n"
			"varying mediump vec4 outputColor;\n"
			"uniform float zNear;\n"
			"uniform float zFar;\n"
			"uniform float frustumScale;\n"

			"uniform vec2 offset;\n"
			"\n"
			"void main()\n"
			"{\n"
			"vec4 cameraPos = vPosition + vec4(offset.x, offset.y, 0.0, 0.0);\n"
			"vec4 clipPos;\n"
			"\n"
			"clipPos.xy = cameraPos.xy * frustumScale;\n"
			//"clipPos.y = cameraPos.y;\n"
			"\n"
			"clipPos.z = cameraPos.z * (zNear + zFar) / (zNear - zFar);\n"
			"clipPos.z += 2.0 * zFar * zNear / (zNear - zFar);\n"
			"\n"
			"clipPos.w = -cameraPos.z;\n"
			"\n"
			//possible cameraPos.z = {-1.15, -1.05}
			//these values are invalid, we should add 1.5
			//"outputColor = vec4(0.0 ,(cameraPos.z + 1.15) * 5.0, 0.0, 1.0);\n"
			//"outputColor = vec4(0.8, 0.0, 0.0, 1.0);\n"
			"outputColor = vColor;"
			"gl_Position = clipPos;\n"
			"}\n";
}

void RacketBar::initializeFragmentShader() {
	FSRacketbarbasic =
			"varying mediump vec4 outputColor;\n"
					"void main() {\n"
					//"gl_FragColor = vec4 ( 0.8, 0.0, 0.0, 1.0 ) + outputColor;\n"
					"gl_FragColor = outputColor;\n"
					"}\n";
}

void RacketBar::initializeVertexPositions() {
	float incomingVertexes[] = {
			 0.5f,  0.05f, -1.25f, // F
			-0.5f,  0.05f, -1.25f, // E
			 0.5f,  0.05f, -1.05f, // B
			-0.5f,  0.05f, -1.05f, // A
			-0.5f, -0.05f, -1.05f, // C
			-0.5f,  0.05f, -1.25f, // E
			-0.5f, -0.05f, -1.25f, // G
			 0.5f, -0.05f, -1.25f, // H
			-0.5f, -0.05f, -1.05f, // C
			 0.5f, -0.05f, -1.05f, // D
			 0.5f,  0.05f, -1.05f, // B
			 0.5f, -0.05f, -1.25f, // H
			 0.5f,  0.05f, -1.25f, // F
			-0.5f,  0.05f, -1.25f, // E


			1.0, 0.0, 0.0, 0.0, // F		//the coloring impacts the triangle that it started
			1.0, 0.0, 0.0, 0.0, // E
			1.0, 0.0, 0.0, 0.0, // B
			1.0, 0.0, 0.0, 0.0, // A
			1.0, 0.0, 0.0, 0.0, // C
			1.0, 0.0, 0.0, 0.0, // E
			1.0, 0.0, 0.0, 0.0, // G
			1.0, 0.0, 0.0, 0.0, // H
			1.0, 0.0, 0.0, 0.0, // C
			1.0, 0.0, 0.0, 0.0, // D
			1.0, 0.0, 0.0, 0.0, // B
			1.0, 0.0, 0.0, 0.0, // H
			1.0, 0.0, 0.0, 0.0, // F
			1.0, 0.0, 0.0, 0.0  // E
			};

			/* colors
			* surfaces are like that:
			* acdb blue
			* abef red
			* bfhd green
			* rest is black

			1.0, 1.0, 0.0, 1.0, // F
			1.0, 0.0, 0.0, 1.0, // E
			1.0, 1.0, 1.0, 1.0, // B
			1.0, 0.0, 0.0, 1.0, // A
			0.0, 0.0, 1.0, 1.0, // C
			1.0, 0.0, 0.0, 1.0, // E
			0.0, 0.0, 0.0, 1.0, // G
			0.0, 1.0, 0.0, 1.0, // H
			0.0, 0.0, 1.0, 1.0, // C
			0.0, 1.0, 1.0, 1.0, // D
			1.0, 1.0, 1.0, 1.0, // B
			0.0, 1.0, 0.0, 1.0, // H
			1.0, 1.0, 0.0, 1.0, // F
			1.0, 0.0, 0.0, 1.0 // E
			};
			*/


	/*float incomingVertexes[] = { -0.5f, -0.05f, 0.0f, // bottom left
	 0.5f, -0.05f, 0.0f, // bottom right
	 -0.5f, 0.05f, 0.0f, // top left
	 0.5f, 0.05, 0.0f // top right
	 };
	 */
	elementPerVertex = 7;
	vertexPositionsSize = sizeof(incomingVertexes);
	vertexPositionsPointer = (float*) malloc(vertexPositionsSize);
	memcpy(vertexPositionsPointer, incomingVertexes, vertexPositionsSize);
	vertexPositionsSize = vertexPositionsSize / sizeof(float);

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
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
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
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertexPositionsSize * sizeof(float),
			vertexPositionsPointer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

RacketBar::RacketBar(bool userBar) {
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
	initializeVertexBuffer();

	positionBufferPointer = glGetAttribLocation(_racketbarGLSLProgram, "vPosition");
	colorInputPointer = glGetAttribLocation(_racketbarGLSLProgram, "vColor");
}

void RacketBar::draw(float position) {

	/*
	 "attribute vec4 vPosition;\n"
	 "\n"
	 "uniform vec2 offset;\n"
	 "uniform float zNear;\n"
	 "uniform float zFar;\n"
	 "uniform float frustumScale;\n"
	 */

	glUseProgram(_racketbarGLSLProgram);

	GLint offsetLocation = glGetUniformLocation(_racketbarGLSLProgram, "offset");
	glUniform2f(offsetLocation, position, fYOffset);

	GLint nearLocation = glGetUniformLocation(_racketbarGLSLProgram, "zNear");
	GLint farLocation = glGetUniformLocation(_racketbarGLSLProgram, "zFar");
	GLint scaleLocation = glGetUniformLocation(_racketbarGLSLProgram, "frustumScale");
	glUniform1f(nearLocation, 1.0f);
	glUniform1f(farLocation, 3.0f);
	glUniform1f(scaleLocation, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(positionBufferPointer);
	glEnableVertexAttribArray(colorInputPointer);

	glVertexAttribPointer(positionBufferPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	int startPoint = vertexPositionsSize * sizeof(float) / elementPerVertex * 3;
	glVertexAttribPointer(colorInputPointer, 4, GL_FLOAT, GL_FALSE, 0, (void *)(startPoint));

	//FIXME 3 should not be hardcoded
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexPositionsSize / elementPerVertex);

	//glDrawElements(GL_TRIANGLES, sizeof(drawOrder),GL_UNSIGNED_SHORT, &drawOrderBufferObject);

	glDisableVertexAttribArray(colorInputPointer);
	glDisableVertexAttribArray(positionBufferPointer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

}
