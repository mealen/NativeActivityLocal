/*
 * openglHelper.cpp
 *
 *  Created on: 28 Mar 2013
 *      Author: Engin Manap
 */

#include "openglHelper.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;

namespace androng {

OpenglHelper::OpenglHelper(int viewHeight, int viewWidth) {
    // Initialize GL state.
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    //glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    //glDisable(GL_DEPTH_TEST);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

	glDisable(GL_CULL_FACE);


    //FIXME there should be checks for extension support
    glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress ( "glGenVertexArraysOES" );
    glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress ( "glBindVertexArrayOES" );
    glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress ( "glDeleteVertexArraysOES" );
    glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC)eglGetProcAddress ( "glIsVertexArrayOES" );

    LOGI("glGenVertexArraysOES %p", glGenVertexArraysOES);
    LOGI("glBindVertexArrayOES %p", glBindVertexArrayOES);
    LOGI("glDeleteVertexArraysOES %p", glDeleteVertexArraysOES);
    LOGI("glIsVertexArrayOES %p", glIsVertexArrayOES);



	rbUser = new RacketBar(true, viewHeight, viewWidth);
	rbCPU = new RacketBar(false, viewHeight, viewWidth);
	ball = new Ball(viewHeight, viewWidth);
}

void OpenglHelper::openglDraw(float bottomRacketPosition) {
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);




	ball->draw(0, 0);

	rbUser->draw(bottomRacketPosition);

	rbCPU->draw(0.25);


}

}
