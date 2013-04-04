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

//using namespace std;

class RacketBar {


private:
	bool isUserBar;
	float fYOffset;
	float* vertexPositionsPointer;
	int vertexPositionsSize;
	GLuint theProgram;
	GLuint positionBufferObject;
	GLuint positionBufferPointer;

	std::string VSbasic;
	std::string FSbasic;
	void initializeVertexShader(){
		VSbasic = "attribute vec4 vPosition;\n"
					"uniform vec2 offset;"
					"void main()\n"
					"{\n"
					"vec4 totalOffset = vec4(offset.x, offset.y, 0.0, 0.0);\n"
					" gl_Position = vPosition + totalOffset;\n"
					"}\n";

	}

	void initializeFragmentShader(){
		FSbasic = "precision mediump float;\n"
		// "uniform vec4 vColor;\n"
						"void main() {\n"
						" gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
						"}\n";
	}

	void initializeVertexPositions(){
		float incomingVertexes[] = { -0.5f, -0.05f, 0.0f, // bottom left
				0.5f, -0.05f, 0.0f, // bottom right
				-0.5f, 0.05f, 0.0f, // top
				0.5f, 0.05, 0.0f // top
				};

		vertexPositionsSize = sizeof(incomingVertexes);

		vertexPositionsPointer = (float*) malloc(vertexPositionsSize);
		memcpy(vertexPositionsPointer, incomingVertexes, vertexPositionsSize);
		vertexPositionsSize = vertexPositionsSize / sizeof(float);

	}

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

			fprintf(stderr, "Compile failure in %s shader:\n%s\n",
					strShaderType, strInfoLog);
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

		float arrayForGL[vertexPositionsSize];
		for(int i=0; i< vertexPositionsSize;i++){
			float* element = vertexPositionsPointer + i;
			LOGI("element %d is %f", i, *element);
			arrayForGL[i] = *element;
			LOGI("arrayForGL[%d] is %f", i, arrayForGL[i]);

		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(arrayForGL), arrayForGL,
				GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
public:


	RacketBar(bool userBar) {
		if(userBar){
			fYOffset = -0.8f;
		} else {
			 fYOffset = 0.8f;
		}
		isUserBar = userBar;
		initializeVertexShader();
		initializeFragmentShader();
		InitializeProgram();
		initializeVertexPositions();
		InitializeVertexBuffer();

		positionBufferPointer = glGetAttribLocation(theProgram, "vPosition");
	}

	void draw(float position) {

		glUseProgram(theProgram);

		GLint offsetLocation = glGetUniformLocation(theProgram, "offset");

		glUniform2f(offsetLocation, position, fYOffset);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glEnableVertexAttribArray(positionBufferPointer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//FIXME 3 should not be hardcoded
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexPositionsSize/ 3);
		//glDrawElements(GL_TRIANGLES, sizeof(drawOrder),GL_UNSIGNED_SHORT, &drawOrderBufferObject);

		glDisableVertexAttribArray(positionBufferPointer);
		glUseProgram(0);
	}

};

