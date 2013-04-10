/*
 * engine.h
 *
 *  Created on: 10 Nis 2013
 *      Author: Engin Manap
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "main.h"

namespace androng {

#define DESIRED_FPS 60.0f

class GameEngine {
private:
	timespec tsStart, tsStop;
	long timeTaken;
	float relativeSpeed;
	android_app* state;
	androidPart::engine* engine;

public:

	GameEngine(android_app* state, struct androidPart::engine* engine);
	void drawFrame();
	void gameLoop();
	void runGame();
	void startTimer();
	void stopTimer();
};

}


#endif /* ENGINE_H_ */
