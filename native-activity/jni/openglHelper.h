/*
 * openglHelper.h
 *
 *  Created on: 15 Nis 2013
 *      Author: engin
 */



#ifndef OPENGLHELPER_H_
#define OPENGLHELPER_H_

#include "RacketBar.cpp"
#include "ball.cpp"

namespace androng {

RacketBar *rbUser;
RacketBar *rbCPU;
Ball *ball;


void initOpengl();
void openglDraw(float);

}
#endif /* OPENGLHELPER_H_ */
