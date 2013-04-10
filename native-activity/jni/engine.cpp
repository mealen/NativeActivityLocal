/*
 * engine.cpp
 *
 *  Created on: 05 Nis 2013
 *      Author: Engin Manap
 */

#include <time.h>
#include <EGL/egl.h>
#include "engine.h"

#include "openglHelper.cpp"


namespace androng {

	GameEngine::GameEngine(android_app* state, struct androidPart::engine* engine){
		this->state = state;
		this->engine = engine;
		LOGI("init engine and Opengl");
	    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	    //glEnable(GL_CULL_FACE);
	    //glShadeModel(GL_SMOOTH);
	    glDisable(GL_DEPTH_TEST);

	    initOpengl();
	}

	void GameEngine::drawFrame(){
	    if (engine->display == NULL) {
	        // No display.
	        return;
	    }
	    //float temp = 0.3f;
	    float temp = static_cast<float>(engine->state.x);
	    temp = (temp / engine->width) - 0.5;
	    openglDraw(temp);

	    eglSwapBuffers(engine->display, engine->surface);
	}

	void GameEngine::gameLoop(){
		//how many times in a sec are we drawing?
		timeTaken =  10e6 / timeTaken;
		//calculate speed relative to what we desired
		relativeSpeed = DESIRED_FPS / timeTaken;
		//we should multiply any movement with relative speed, this way game works same speed in all environments.
		androidPart::processEvents(state,engine);
		//androidPart::processEvents(state, engine);
		drawFrame();
		stopTimer();
		startTimer();
	}

	void GameEngine::runGame(){
		while(0 == 0){
			gameLoop();
		}
	}


	void GameEngine::startTimer(){
		clock_gettime(CLOCK_REALTIME, &tsStart);
	}

	void GameEngine::stopTimer(){
		clock_gettime(CLOCK_REALTIME, &tsStop);
		timeTaken = tsStop.tv_nsec - tsStart.tv_nsec;
	}

}

