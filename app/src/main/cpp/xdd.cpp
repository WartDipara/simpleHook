#include <jni.h>
#include <pthread.h>
#include <dlfcn.h>
#include <unistd.h>
#include <android/log.h>
#include "dobby.h"

/**
 * 小虾米战三国
 */
enum RetStatus { RS_SUCCESS = 0 };

#define TAG "SpeedHook"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)


static float g_currentSpeed = 1.0f;
static bool g_hookInstalled = false;
namespace cocos2d {
    class Scheduler;
}

using SchedUpdate_t = void(*)(cocos2d::Scheduler*, float);
static SchedUpdate_t origSchedulerUpdate = nullptr;

// Hook实现
static void hookedSchedulerUpdate(cocos2d::Scheduler* thiz, float dt) {
    float modifiedDt = dt * g_currentSpeed;
    origSchedulerUpdate(thiz, modifiedDt);
}

// 开线程跑
static void* hookThread(void*) {
    void* handle = nullptr;
    int attempts = 0;

    while (handle == nullptr && attempts < 150) {
        handle = dlopen("libcocos2dlua.so", RTLD_NOW);
        if (handle == nullptr) {
            usleep(200000);
            attempts++;
        }
    }

    if (handle == nullptr) {
        LOGE("Failed to load libcocos2dlua.so after 30s");
        return nullptr;
    }

    LOGI("libcocos2dlua.so loaded successfully");

    // 查找 Scheduler::update(float) 符号
    // 符号: _ZN7cocos2d9Scheduler6updateEf
    void* symUpdate = dlsym(handle, "_ZN7cocos2d9Scheduler6updateEf");

    if (symUpdate == nullptr) {
        LOGE("Failed to find Scheduler::update symbol");
        LOGE("dlerror: %s", dlerror());
        return nullptr;
    }

    LOGI("Found Scheduler::update at %p", symUpdate);

    // 安装 Hook
    if (DobbyHook(symUpdate, (void*)hookedSchedulerUpdate, (void**)&origSchedulerUpdate) == RS_SUCCESS) {
        g_hookInstalled = true;
        LOGI("Scheduler::update Hook installed successfully");
        LOGI("Current speed: %.2fx", g_currentSpeed);
    } else {
        LOGE("Failed to install Hook");
    }

    return nullptr;
}


/**
 * JNI接口
 */
 extern "C"{
 JNIEXPORT void JNICALL
 Java_com_ray_snxyjde_NativeLib_callBoost(JNIEnv*, jclass) {

     g_currentSpeed = 2.0f;
     LOGI("speed set to %.2fx", g_currentSpeed);
 }

 JNIEXPORT void JNICALL
 Java_com_ray_snxyjde_NativeLib_callNormal(JNIEnv*, jclass) {
     g_currentSpeed = 1.0f;
     LOGI("speed set to %.2fx", g_currentSpeed);
 }

 JNIEXPORT void JNICALL
 Java_com_ray_snxyjde_NativeLib_callSlowdown(JNIEnv*, jclass) {

     g_currentSpeed = 0.5f;
     LOGI("speed set to %.2fx", g_currentSpeed);
 }

 JNIEXPORT jfloat JNICALL
 Java_com_ray_snxyjde_NativeLib_getCurrentSpeed(JNIEnv*, jclass) {
     LOGI("getCurrentSpeed called: %.2fx", g_currentSpeed);
     return g_currentSpeed;
 }

 JNIEXPORT void JNICALL
 Java_com_ray_snxyjde_NativeLib_setCustomSpeed(JNIEnv*, jclass, jfloat speed) {
     // 限制速度范围在 0.1x - 10.0x 之间
     if (speed < 0.1f) speed = 0.1f;
     if (speed > 10.0f) speed = 10.0f;

     g_currentSpeed = speed;
     LOGI("⚡ Custom speed set to %.2fx (Hook installed: %s)",
          g_currentSpeed, g_hookInstalled ? "YES" : "NO");
 }
 }



// JNI 初始化
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
    // 创建后台线程安装 Hook
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&thread, &attr, hookThread, nullptr) != 0) {
        LOGE("Failed to create hook thread");
    }
    pthread_attr_destroy(&attr);
    return JNI_VERSION_1_6;
}