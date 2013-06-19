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
	android_app* state;
	androidPart::engine* androidEngine;


	timespec tsStart, tsStop;
	long timeTaken;
	float relativeSpeed;
	OpenglHelper* oglHelper;

	float ballX;
	float ballY;

	float ballDeltaX;
	float ballDeltaY;

	float borderX;
	float borderY;

	void game();
	void drawFrame(float, float);
	bool moveBall(float);
	void setBorders(int, int);

public:
	void initOpengl(OpenglHelper*&);
	GameEngine(android_app *state, androidPart::engine *androidEngine);
	void runGame();
	void startTimer();
	void stopTimer();
};


}

#endif /* ENGINE_H_ */
