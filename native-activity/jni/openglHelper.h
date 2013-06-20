/*
 * openglHelper.h
 *
 *  Created on: 15 Nis 2013
 *      Author: engin
 */

#ifndef OPENGLHELPER_H_
#define OPENGLHELPER_H_

#include "RacketBar.h"
#include "Ball.h"

extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
extern PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;

namespace androng {

class OpenglHelper {
private:
	RacketBar *rbUser;
	RacketBar *rbCPU;
	Ball *ball;

public:

	OpenglHelper(int, int);
	void openglDraw(float, float, float);
	float getRacketWidth();
	float getRacketPosition(bool);
};

}
#endif /* OPENGLHELPER_H_ */
