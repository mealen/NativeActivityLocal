/*
 * GameEngine.cpp
 *
 *  Created on: 12 Nis 2013
 *      Author: engin
 */

#include "GameEngine.h"


namespace androng {

GameEngine::GameEngine() {
	relativeSpeed = 1.0f;
	timeTaken = 0;
	//initOpengl();
}

void GameEngine::startTimer() {
	clock_gettime(CLOCK_REALTIME, &tsStart);
}

void GameEngine::stopTimer() {
	clock_gettime(CLOCK_REALTIME, &tsStop);
	timeTaken = tsStop.tv_nsec - tsStart.tv_nsec;
}

void GameEngine::runGame(android_app *state,
		androidPart::engine *androidEngine) {
	//while (0 == 0) {
	androidPart::processEvents(state, androidEngine);
	game(androidEngine);
	//}
}

void GameEngine::game(androidPart::engine *androidEngine) {
//how many times in a sec are we drawing?
	timeTaken = 10e6 / timeTaken;
//calculate speed relative to what we desired
	relativeSpeed = DESIRED_FPS / timeTaken;
//we should multiply any movement with relative speed, this way game works same speed in all environments.
	//androidPart::processEvents(state, androidEngine);
//androidPart::processEvents(state, engine);
	//drawFrame(androidEngine);
	stopTimer();
	startTimer();
	LOGI("time for frame is %ld", timeTaken);
}

void GameEngine::drawFrame(androidPart::engine * androidEngine) {
	if (androidEngine->display == NULL) {
// No display.
		return;
	}
//float temp = 0.3f;
	float temp = static_cast<float>(androidEngine->state.x);
	temp = (temp / androidEngine->width) - 0.5;
	//openglDraw(temp);

	eglSwapBuffers(androidEngine->display, androidEngine->surface);
}

}
