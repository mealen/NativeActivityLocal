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
    // Initialize GL state.
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    //glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

	rbUser = new RacketBar(true);
	rbCPU = new RacketBar(false);
	ball = new Ball();
}

void OpenglHelper::openglDraw(float position) {
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT);
	//RacketBar rb;
	rbUser->draw(position);
	rbCPU->draw(0.25);
	ball->draw(0, 0);
}

}
