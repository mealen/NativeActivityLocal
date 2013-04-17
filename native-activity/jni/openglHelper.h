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

namespace androng {

class OpenglHelper {
private:
	RacketBar *rbUser;
	RacketBar *rbCPU;
	Ball *ball;
public:

	OpenglHelper();
	void openglDraw(float);
};

}
#endif /* OPENGLHELPER_H_ */
