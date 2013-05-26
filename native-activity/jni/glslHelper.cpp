/*
 * glslHelper.cpp
 *
 *  Created on: 22 May 2013
 *      Author: engin
 */

#include "glslHelper.h"

namespace androng{


GLuint GLSLHelper::CreateShader(GLenum eShaderType,
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
		LOGE("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

GLuint GLSLHelper::CreateProgram(const std::vector<GLuint> &shaderList) {
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
		LOGE("Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(racketGLSLProgram, shaderList[iLoop]);
	return racketGLSLProgram;
}

}


