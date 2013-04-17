/*
 * GameEngine.h
 *
 * Created on: 10 Nis 2013
 * Author: Engin Manap
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "time.h"
#include "main.h"
#include "OpenglHelper.h"

#define DESIRED_FPS 60.0f


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

namespace androng {

class GameEngine {
private:
	timespec tsStart, tsStop;
	long timeTaken;
	float relativeSpeed;
	OpenglHelper* oglHelper;

	void game(androidPart::engine *androidEngine);
	void drawFrame(androidPart::engine *androidEngine);

public:

	GameEngine(OpenglHelper*&);
	void runGame(android_app *state, androidPart::engine *androidEngine);
	void startTimer();
	void stopTimer();
};


}

#endif /* ENGINE_H_ */
