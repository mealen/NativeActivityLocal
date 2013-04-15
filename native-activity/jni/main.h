/*
* main.h
*
* Created on: 10 Nis 2013
* Author: engin
*/

#ifndef MAIN_H_
#define MAIN_H_

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <jni.h>
#include <errno.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))


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


 bool processEvents(android_app* state, androidPart::engine* androidEngine);

}
#endif /* MAIN_H_ */
