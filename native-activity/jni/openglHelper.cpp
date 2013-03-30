/*
 * openglHelper.cpp
 *
 *  Created on: 28 Mar 2013
 *      Author: Engin Manap
 */

#include <string>
#include <vector>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <algorithm>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

const std::string VSbasic(
		"attribute vec4 vPosition;\n"
		"uniform vec2 offset;"
		"void main()\n"
		"{\n"
		"vec4 totalOffset = vec4(offset.x, offset.y, 0.0, 0.0);"
		" gl_Position = vPosition + totalOffset;\n"
		"}\n");

const std::string FSbasic(	"precision mediump float;\n"
		// "uniform vec4 vColor;\n"
		"void main() {\n"
		" gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
		"}\n");

const float vertexPositions[] = {
		-0.5f, -0.05f, 0.0f,   // bottom left
		0.5f, -0.05f, 0.0f,// bottom right
		-0.5f, 0.05f, 0.0f,   // top
		0.5f, 0.05, 0.0f,   // top
		};

const short drawOrder[] = {1,2,3};

GLuint theProgram;
GLuint positionBufferObject;
GLuint positionBufferPointer;



GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile) {
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

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType,strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}


GLuint CreateProgram(const std::vector<GLuint> &shaderList) {
	GLuint program = glCreateProgram();

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);

	return program;
}

void InitializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, VSbasic));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, FSbasic));

	theProgram = CreateProgram(shaderList);

	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

void InitializeVertexBuffer() {
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions,
			GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void initOpengl() {
	InitializeProgram();
	InitializeVertexBuffer();

	positionBufferPointer = glGetAttribLocation(theProgram, "vPosition");
}

void openglDraw(float position) {
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);
	float fYOffset = -0.5f;
	GLint offsetLocation = glGetUniformLocation(theProgram, "offset");

    glUniform2f(offsetLocation, position, fYOffset);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(positionBufferPointer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertexPositions));
	//glDrawElements(GL_TRIANGLES, sizeof(drawOrder),GL_UNSIGNED_SHORT, &drawOrderBufferObject);


	glDisableVertexAttribArray(positionBufferPointer);
	glUseProgram(0);
}

