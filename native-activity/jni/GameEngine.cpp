/*
 * GameEngine.cpp
 *
 *  Created on: 12 Nis 2013
 *      Author: engin
 */

#include "GameEngine.h"


namespace androng {

GameEngine::GameEngine(android_app *state, androidPart::engine *androidEngine) {
	this->state = state;
	this->androidEngine = androidEngine;
	relativeSpeed = 1.0f;
	timeTaken = 1l;
	startTimer(); // we process by stop/start, so start would be empty the first

}

void GameEngine::initOpengl(OpenglHelper*& openglHelper){

	oglHelper = new OpenglHelper();

	openglHelper = oglHelper;
	//draw 1 frame
	drawFrame();
}

void GameEngine::startTimer() {
	clock_gettime(CLOCK_REALTIME, &tsStart);
}

void GameEngine::stopTimer() {
	clock_gettime(CLOCK_REALTIME, &tsStop);
	timeTaken = tsStop.tv_nsec - tsStart.tv_nsec;
}

void GameEngine::runGame() {
	//while (0 == 0) {
	if(androidPart::processEvents(state, androidEngine))
		return;
	game();
	//}
}

void GameEngine::game() {
	stopTimer();
	startTimer();
//how many times in a sec are we drawing?
	timeTaken = 10e6 / timeTaken;

//calculate speed relative to what we desired
	relativeSpeed = DESIRED_FPS / timeTaken;
//we should multiply any movement with relative speed, this way game works same speed in all environments.

	drawFrame();

}

void GameEngine::drawFrame() {
	if (androidEngine->display == NULL) {
// No display.
		return;
	}
//float temp = 0.3f;
	float temp = static_cast<float>(androidEngine->state.x);
	temp = (temp / androidEngine->width) - 0.5;
	oglHelper->openglDraw(temp);

	eglSwapBuffers(androidEngine->display, androidEngine->surface);
}

}
