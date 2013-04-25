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
	void RacketBar::initializeVertexShader(){
		VSbasic = "attribute vec4 vPosition;\n"
		"uniform vec2 offset;\n"
		"\n"
		"void main()\n"
		"{\n"
			"vec4 cameraPos = vPosition + vec4(offset.x, offset.y, 0.0, 0.0);\n"
			"vec4 clipPos;\n"
			"\n"
			"clipPos.x = cameraPos.x;\n"
			"clipPos.y = cameraPos.y;\n"
			"\n"
			"clipPos.z = cameraPos.z * (1.0 + 3.0) / (1.0 - 3.0);\n"
			"clipPos.z += 2.0 * 3.0 / (1.0 - 3.0);\n"
			"\n"
			"clipPos.w = -cameraPos.z;\n"
			"\n"
			"gl_Position = clipPos;\n"
		"}\n";
	}

	void RacketBar::initializeFragmentShader() {
		FSbasic = "precision mediump float;\n"
		// "uniform vec4 vColor;\n"
						"void main() {\n"
						" gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
						"}\n";
	}

	void RacketBar::initializeVertexPositions() {
		float incomingVertexes[] = {
				 0.5f,  0.05f, -1.15f, 	// F
				-0.5f,  0.05f, -1.15f, 	// E
				 0.5f,  0.05f, -1.05f,	// B
				-0.5f,  0.05f, -1.15f,	// A
				-0.5f, -0.05f, -1.05f,	// C
				-0.5f,  0.05f, -1.15f, 	// E
				-0.5f, -0.05f, -1.15f, 	// G
				 0.5f, -0.05f, -1.15f, 	// H
				-0.5f, -0.05f, -1.05f,	// C
				 0.5f, -0.05f, -1.05f,	// D
				 0.5f,  0.05f, -1.05f,	// B
				 0.5f, -0.05f, -1.15f, 	// H
				 0.5f,  0.05f, -1.15f, 	// F
				-0.5f,  0.05f, -1.15f 	// E
		};

		/*float incomingVertexes[] = { -0.5f, -0.05f, 0.0f, // bottom left
				0.5f, -0.05f, 0.0f, // bottom right
				-0.5f, 0.05f, 0.0f, // top left
				0.5f, 0.05, 0.0f // top right
				};
*/
		elementPerVertex = 3;
		vertexPositionsSize = sizeof(incomingVertexes);
		vertexPositionsPointer = (float*) malloc(vertexPositionsSize);
		memcpy(vertexPositionsPointer, incomingVertexes, vertexPositionsSize);
		vertexPositionsSize = vertexPositionsSize / sizeof(float);

	}

	GLuint RacketBar::CreateShader(GLenum eShaderType, const std::string &strShaderFile) {
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

	void RacketBar::initializeProgram() {
		std::vector<GLuint> shaderList;

		shaderList.push_back(CreateShader(GL_VERTEX_SHADER, VSbasic));
		shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, FSbasic));

		theProgram = CreateProgram(shaderList);

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
		if(userBar){
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

		positionBufferPointer = glGetAttribLocation(theProgram, "vPosition");
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

		glUseProgram(theProgram);

		GLint offsetLocation = glGetUniformLocation(theProgram, "offset");


		glUniform2f(offsetLocation, position, fYOffset);

		glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		glEnableVertexAttribArray(positionBufferPointer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//FIXME 3 should not be hardcoded
		glDrawArrays(GL_TRIANGLE_STRIP, 0,
				vertexPositionsSize / elementPerVertex);
		//glDrawElements(GL_TRIANGLES, sizeof(drawOrder),GL_UNSIGNED_SHORT, &drawOrderBufferObject);

		glDisableVertexAttribArray(positionBufferPointer);
		glUseProgram(0);
	}

}
