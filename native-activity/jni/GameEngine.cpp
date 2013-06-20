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
	this->ballX = 0;
	this->ballY = 0;
	this->ballDeltaX = 0.05;
	this->ballDeltaY = 0.03;
	startTimer(); // we process by stop/start, so start would be empty the first

}

void GameEngine::setBorders(int windowHeight, int windowWidth) {
	borderX = (float) windowWidth / (float) windowHeight;
	borderY = 1.0;
}



void GameEngine::initOpengl(OpenglHelper*& openglHelper) {

	oglHelper = new OpenglHelper(this->androidEngine->height,
			this->androidEngine->width);

	openglHelper = oglHelper;

	setBorders(this->androidEngine->height, this->androidEngine->width);
	//draw 1 frame
	//set the bar to middle
	int32_t tempStateX = androidEngine->state.x;
	androidEngine->state.x = androidEngine->width / 2;
	drawFrame(ballX, ballY);
	androidEngine->state.x = tempStateX;

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
	//androidEngine->animating = 0;
	if (androidPart::processEvents(state, androidEngine))
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

	moveBall(relativeSpeed);
	drawFrame(ballX, ballY);

}

bool GameEngine::moveBall(float speed) {
	bool returnX = true;
	bool returnY = true;
	if ((ballX + ballDeltaX) > borderX) {
		float tempDelta = ballDeltaX;
		ballDeltaX = borderX - ballX;
		ballX = borderX - ballDeltaX;
		ballDeltaX = -1 * tempDelta;
	} else {
		if ((ballX + ballDeltaX) < (-1 * borderX)) {
			float tempDelta = ballDeltaX;
			ballDeltaX = (-1 * borderX) - (ballDeltaX + ballX);
			ballX = ballDeltaX + (-1 * borderX);
			ballDeltaX = -1 * tempDelta;
		} else {
			if ((ballX + ballDeltaX) == (-1 * borderX)) {
				ballX = (-1 * borderX);
				ballDeltaX = ballDeltaX * -1;
			} else {
				if ((ballX - ballDeltaX) == borderX) {
					ballX = borderX;
					ballDeltaX = ballDeltaX * -1;
				} else {
					ballX += ballDeltaX;
					returnX = false;
				}
			}
		}

	}

	if ((ballY + ballDeltaY) > borderY) {
		float tempDelta = ballDeltaY;
		ballDeltaY = borderY - ballY;
		ballY = borderY - ballDeltaY;
		ballDeltaY = -1 * tempDelta;
	} else {
		if ((ballY + ballDeltaY) < (-1 * borderY)) {
			float tempDelta = ballDeltaY;
			ballDeltaY = (-1 * borderY) - (ballDeltaY + ballY);
			ballY = ballDeltaY + (-1 * borderY);
			ballDeltaY = -1 * tempDelta;
		} else {
			if ((ballY + ballDeltaY) == (-1 * borderY)) {
				ballY = (-1 * borderY);
				ballDeltaY = ballDeltaY * -1;
			} else {
				if ((ballY + ballDeltaY) == borderY) {
					ballY = borderY;
					ballDeltaY = ballDeltaY * -1;
				} else {
					ballY += ballDeltaY;
					returnY = false;
				}
			}
		}
	}

	float RACKETOFFSET = 0.8;
	float RACKETHALFHEIGHT = 0.05;
	float BALLRADIUS = 0.1;
	if ((ballY + ballDeltaY) > (RACKETOFFSET - RACKETHALFHEIGHT)) {
		if((ballX + ballDeltaX) <= (oglHelper->getRacketPosition(false) + oglHelper->getRacketWidth() + BALLRADIUS)){ // not pass from right
			if((ballX + ballDeltaX) >= (oglHelper->getRacketPosition(false) - oglHelper->getRacketWidth() - BALLRADIUS)){ //not pass from left
					ballY= ballY - ballDeltaY * 2;
					ballDeltaY = -1 * ballDeltaY;
			}
		}
	} else if ((ballY + ballDeltaY) < (-1 * RACKETOFFSET + RACKETHALFHEIGHT)) {
		if((ballX + ballDeltaX) <= (oglHelper->getRacketPosition(true) + oglHelper->getRacketWidth() + BALLRADIUS)){ // not pass from right
			if((ballX + ballDeltaX) >= (oglHelper->getRacketPosition(true) - oglHelper->getRacketWidth() - BALLRADIUS)){ //not pass from left
					ballY= ballY - ballDeltaY * 2;
					ballDeltaY = -1 * ballDeltaY;
			}
		}
	}

	return (returnX || returnY);
}

void GameEngine::drawFrame(float ballX, float ballY) {
	if (androidEngine->display == NULL) {
		// No display.
		return;
	}
	//float temp = 0.3f;
	float temp = static_cast<float>(androidEngine->state.x);
	temp = (temp / androidEngine->width) - 0.5;
	temp = temp * 2;

	float racketBarHalfSize = oglHelper->getRacketWidth();
	if(temp <( -1 + racketBarHalfSize )){
		temp = -1 + racketBarHalfSize;
	} else {
		if(temp >( 1 - racketBarHalfSize)){
			temp = 1 - racketBarHalfSize;
		}
	}
	temp = temp * borderX;

	oglHelper->openglDraw(temp, ballX, ballY);

	eglSwapBuffers(androidEngine->display, androidEngine->surface);
}

}
