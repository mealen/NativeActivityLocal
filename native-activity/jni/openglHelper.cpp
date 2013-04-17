/*
 * openglHelper.cpp
 *
 *  Created on: 28 Mar 2013
 *      Author: Engin Manap
 */

#include "openglHelper.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace androng {

OpenglHelper::OpenglHelper() {
	rbUser = new RacketBar(true);
	rbCPU = new RacketBar(false);
	ball = new Ball();
}

void OpenglHelper::openglDraw(float position) {
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT);
	//RacketBar rb;
	rbUser->draw(position);
	rbCPU->draw(0);
	ball->draw(0, 0);
}

}
