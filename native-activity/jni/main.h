/*
 * main.h
 *
 *  Created on: 10 Nis 2013
 *      Author: engin
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <android_native_app_glue.h>
#include <android/sensor.h>



namespace androidPart {
/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};


 int processEvents(android_app* state, androidPart::engine* engine);

}
#endif /* MAIN_H_ */
