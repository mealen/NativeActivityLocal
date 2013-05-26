/*
 * glslHelper.h
 *
 *  Created on: 22 May 2013
 *      Author: engin
 */

#ifndef GLSLHELPER_H_
#define GLSLHELPER_H_

#include <GLES2/gl2.h>
#include <android/log.h>
#include <vector>
#include <string>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
namespace androng {
class GLSLHelper {
public:
	static GLuint CreateShader(GLenum, const std::string &);
	static GLuint CreateProgram(const std::vector<GLuint>&);
};

}

#endif /* GLSLHELPER_H_ */
