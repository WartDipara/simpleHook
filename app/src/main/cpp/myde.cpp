#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <mutex>
#include "dobby.h"
/**
 * 少年西游记
 */
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "Hook", __VA_ARGS__)

static float g_current_speed = 1.0f;
static float g_native_speed  = 1.0f;
static std::mutex g_speed_mutex;
static std::once_flag g_hook_once;

using UpdateFn = void (*)(void*, float);

static UpdateFn g_origTrackEntryUpdate        = nullptr;
static UpdateFn g_origAnimationStateUpdate    = nullptr;
static UpdateFn g_origSkeletonAnimationUpdate = nullptr;
static UpdateFn g_origSkeletonCacheUpdate     = nullptr;

static float get_scaled_dt(float dt) {
    return dt * g_native_speed;
}

static bool hook_symbol(const char* symbol, void* replace, void** original) {
    void* target = dlsym(RTLD_DEFAULT, symbol);
    if (!target) {
        LOG("symbol %s not found", symbol);
        return false;
    }

    int ret = DobbyHook(target, replace, original);
    if (ret != 0) {
        LOG("hook %s failed, ret=%d", symbol, ret);
        return false;
    }
    LOG("hook %s success, original=%p", symbol, *original);
    return true;
}

static void TrackEntry_update_hook(void* self, float dt) {
    if (g_origTrackEntryUpdate) g_origTrackEntryUpdate(self, get_scaled_dt(dt));
}
static void AnimationState_update_hook(void* self, float dt) {
    if (g_origAnimationStateUpdate) g_origAnimationStateUpdate(self, get_scaled_dt(dt));
}
static void SkeletonAnimation_update_hook(void* self, float dt) {
    if (g_origSkeletonAnimationUpdate) g_origSkeletonAnimationUpdate(self, get_scaled_dt(dt));
}
static void SkeletonCacheAnimation_update_hook(void* self, float dt) {
    if (g_origSkeletonCacheUpdate) g_origSkeletonCacheUpdate(self, get_scaled_dt(dt));
}

static void install_spine_hooks() {
    hook_symbol("_ZN5spine10TrackEntry6updateEf",
                (void*)TrackEntry_update_hook,
                (void**)&g_origTrackEntryUpdate);

    hook_symbol("_ZN5spine14AnimationState6updateEf",
                (void*)AnimationState_update_hook,
                (void**)&g_origAnimationStateUpdate);

    hook_symbol("_ZN5spine17SkeletonAnimation6updateEf",
                (void*)SkeletonAnimation_update_hook,
                (void**)&g_origSkeletonAnimationUpdate);

    hook_symbol("_ZN5spine22SkeletonCacheAnimation6updateEf",
                (void*)SkeletonCacheAnimation_update_hook,
                (void**)&g_origSkeletonCacheUpdate);
}

static void set_native_speed(float scale) {
    g_native_speed = scale <= 0.f ? 0.f : scale;
    LOG("SpeedHack: native speed set %.3f", g_native_speed);
}

/**
 * JS注入
 * @param env
 * @param speed
 */
static void apply_speed(JNIEnv *env, float speed) {
    std::call_once(g_hook_once, install_spine_hooks);
    set_native_speed(speed);

    char js[16384];
    snprintf(js, sizeof(js),
             "(function(){"
             "try{"
             "var scale=%.4f;"
             "if(!window.__SpeedHack){"
             "window.__SpeedHack={"
             "installed:false,"
             "director:null,"
             "scheduler:null,"
             "actionMgr:null,"
             "animationMgr:null,"
             "tweenSys:null,"
             "install:function(){"
             "var ccGlobal=window.cc;"
             "if(!ccGlobal||!ccGlobal.director){return false;}"
             "var director=ccGlobal.director;"
             "this.director=director;"
             "if(!director.__speedHackPatched&&director.calculateDeltaTime){"
             "director.__speedHackPatched=true;"
             "director.__speedHackScale=1;"
             "director.__originCalculateDeltaTime=director.calculateDeltaTime.bind(director);"
             "director.calculateDeltaTime=function(now){"
             "this.__originCalculateDeltaTime(now);"
             "this._deltaTime*=this.__speedHackScale||1;"
             "};"
             "}"
             "var scheduler=director.getScheduler?director.getScheduler():director._scheduler;"
             "if(scheduler&&!scheduler.__speedHackPatched&&scheduler.update){"
             "this.scheduler=scheduler;"
             "scheduler.__speedHackPatched=true;"
             "scheduler.__speedHackScale=1;"
             "scheduler.__originUpdate=scheduler.update.bind(scheduler);"
             "scheduler.update=function(dt){"
             "this.__originUpdate(dt*(this.__speedHackScale||1));"
             "};"
             "scheduler.__speedHackSetScale=function(scale){"
             "this.__speedHackScale=scale;"
             "if(this.setTimeScale){this.setTimeScale(scale);}else{this.timeScale=scale;}"
             "};"
             "}"
             "var actionMgr=director.getActionManager?director.getActionManager():director._actionManager;"
             "if(actionMgr&&!actionMgr.__speedHackPatched&&actionMgr.update){"
             "this.actionMgr=actionMgr;"
             "actionMgr.__speedHackPatched=true;"
             "actionMgr.__speedHackScale=1;"
             "actionMgr.__originUpdate=actionMgr.update.bind(actionMgr);"
             "actionMgr.update=function(dt){"
             "this.__originUpdate(dt*(this.__speedHackScale||1));"
             "};"
             "}"
             "var animationMgr=director.getAnimationManager?director.getAnimationManager():director._animationManager;"
             "if(animationMgr&&!animationMgr.__speedHackPatched&&animationMgr.update){"
             "this.animationMgr=animationMgr;"
             "animationMgr.__speedHackPatched=true;"
             "animationMgr.__speedHackScale=1;"
             "animationMgr.__originUpdate=animationMgr.update.bind(animationMgr);"
             "animationMgr.update=function(dt){"
             "this.__originUpdate(dt*(this.__speedHackScale||1));"
             "};"
             "}"
             "var tweenSys=null;"
             "if(ccGlobal.TweenSystem&&ccGlobal.TweenSystem.instance){"
             "tweenSys=ccGlobal.TweenSystem.instance;"
             "}else if(director._compScheduler&&director._compScheduler._tweenSystem){"
             "tweenSys=director._compScheduler._tweenSystem;"
             "}"
             "if(tweenSys&&!tweenSys.__speedHackPatched&&tweenSys.update){"
             "this.tweenSys=tweenSys;"
             "tweenSys.__speedHackPatched=true;"
             "tweenSys.__speedHackScale=1;"
             "tweenSys.__originUpdate=tweenSys.update.bind(tweenSys);"
             "tweenSys.update=function(dt){"
             "this.__originUpdate(dt*(this.__speedHackScale||1));"
             "};"
             "}"
             "if(window.sp&&sp.Skeleton&&sp.Skeleton.prototype&&!sp.Skeleton.prototype.__speedHackPatched&&sp.Skeleton.prototype.update){"
             "sp.Skeleton.prototype.__speedHackPatched=true;"
             "sp.Skeleton.prototype.__originUpdate=sp.Skeleton.prototype.update;"
             "sp.Skeleton.prototype.update=function(dt){"
             "return this.__originUpdate.call(this,dt*((window.__GLOBAL_TIME_SCALE)||1));"
             "};"
             "}"
             "if(ccGlobal.Animation&&ccGlobal.Animation.prototype&&!ccGlobal.Animation.prototype.__speedHackPatched&&ccGlobal.Animation.prototype.update){"
             "ccGlobal.Animation.prototype.__speedHackPatched=true;"
             "ccGlobal.Animation.prototype.__originUpdate=ccGlobal.Animation.prototype.update;"
             "ccGlobal.Animation.prototype.update=function(dt){"
             "return this.__originUpdate.call(this,dt*((window.__GLOBAL_TIME_SCALE)||1));"
             "};"
             "}"
             "if(ccGlobal.Node&&ccGlobal.Node.prototype&&!ccGlobal.Node.prototype.__speedHackPatched){"
             "ccGlobal.Node.prototype.__speedHackPatched=true;"
             "var originGet=ccGlobal.Node.prototype.getScheduler;"
             "ccGlobal.Node.prototype.getScheduler=function(){"
             "var s=originGet?originGet.call(this):null;"
             "if(!s){"
             "var d=cc.director;"
             "s=(d&&d.getScheduler)?d.getScheduler():((d&&d._scheduler)?d._scheduler:null);"
             "}"
             "return s;"
             "};"
             "}"
             "this.installed=true;"
             "return true;"
             "},"
             "flush:function(){"
             "var director=this.director;"
             "if(!director) return;"
             "try{"
             "if(director.__originCalculateDeltaTime){"
             "var now=(performance&&performance.now)?performance.now():Date.now();"
             "director.__originCalculateDeltaTime(now);"
             "}"
             "}catch(e){console&&console.warn&&console.warn('SpeedHack flush delta error',e);}"
             "try{"
             "var scheduler=this.scheduler||(director.getScheduler&&director.getScheduler());"
             "if(scheduler&&scheduler.__originUpdate){scheduler.__originUpdate(0);}else if(scheduler&&scheduler.update){scheduler.update(0);}"
             "}catch(e){console&&console.warn&&console.warn('SpeedHack flush scheduler error',e);}"
             "try{"
             "if(this.actionMgr&&this.actionMgr.__originUpdate){this.actionMgr.__originUpdate(0);}else if(this.actionMgr&&this.actionMgr.update){this.actionMgr.update(0);}"
             "}catch(e){console&&console.warn&&console.warn('SpeedHack flush action error',e);}"
             "try{"
             "if(this.animationMgr&&this.animationMgr.__originUpdate){this.animationMgr.__originUpdate(0);}else if(this.animationMgr&&this.animationMgr.update){this.animationMgr.update(0);}"
             "}catch(e){console&&console.warn&&console.warn('SpeedHack flush animation error',e);}"
             "try{"
             "if(this.tweenSys&&this.tweenSys.__originUpdate){this.tweenSys.__originUpdate(0);}else if(this.tweenSys&&this.tweenSys.update){this.tweenSys.update(0);}"
             "}catch(e){console&&console.warn&&console.warn('SpeedHack flush tween error',e);}"
             "},"
             "apply:function(scale){"
             "if(!this.director){return;}"
             "this.director.__speedHackScale=scale;"
             "if(this.scheduler){"
             "if(this.scheduler.__speedHackSetScale){"
             "this.scheduler.__speedHackSetScale(scale);"
             "}else if(this.scheduler.setTimeScale){"
             "this.scheduler.setTimeScale(scale);"
             "}else{"
             "this.scheduler.timeScale=scale;"
             "this.scheduler.__speedHackScale=scale;"
             "}"
             "}"
             "if(this.actionMgr){"
             "if(this.actionMgr.setTimeScale){"
             "this.actionMgr.setTimeScale(scale);"
             "}else if(this.actionMgr.setSpeed){"
             "this.actionMgr.setSpeed(scale);"
             "}else{"
             "this.actionMgr.__speedHackScale=scale;"
             "}"
             "}"
             "if(this.animationMgr){"
             "if(this.animationMgr.setTimeScale){"
             "this.animationMgr.setTimeScale(scale);"
             "}else{"
             "this.animationMgr.__speedHackScale=scale;"
             "}"
             "}"
             "if(this.tweenSys){"
             "if(this.tweenSys.setTimeScale){"
             "this.tweenSys.setTimeScale(scale);"
             "}else if(typeof this.tweenSys.timeScale!=='undefined'){"
             "this.tweenSys.timeScale=scale;"
             "}"
             "this.tweenSys.__speedHackScale=scale;"
             "}"
             "window.__GLOBAL_TIME_SCALE=scale;"
             "if(window.CacheAsset&&CacheAsset.Instance){"
             "CacheAsset.Instance.fightSpeed=scale;"
             "CacheAsset.Instance.fightSpeedRate=scale;"
             "}"
             "if(window.GameLogicManager){"
             "if(!GameLogicManager.__originalUpdate&&GameLogicManager.update){"
             "GameLogicManager.__originalUpdate=GameLogicManager.update;"
             "}"
             "if(GameLogicManager.__originalUpdate){"
             "GameLogicManager.update=function(dt){"
             "return this.__originalUpdate(dt*(window.__GLOBAL_TIME_SCALE||1));"
             "};"
             "}"
             "}"
             "},"
             "setScale:function(scale){"
             "if(!this.installed){"
             "if(!this.install()){"
             "var self=this;"
             "setTimeout(function(){self.setScale(scale);},100);"
             "return;"
             "}"
             "}"
             "this.apply(scale);"
             "this.flush();"
             "}"
             "};"
             "}"
             "window.__SpeedHack.setScale(scale);"
             "return true;"
             "}catch(e){"
             "if(window.console&&console.error){console.error('SpeedHack apply failed',e);}"
             "return false;"
             "}"
             "})();",
             speed);

    jclass cls = env->FindClass("com/ray/snxyjde/SpeedUtil");
    if (cls) {
        jmethodID method = env->GetStaticMethodID(cls, "executeLua", "(Ljava/lang/String;)V");
        if (method) {
            jstring jsStr = env->NewStringUTF(js);
            env->CallStaticVoidMethod(cls, method, jsStr);
            env->DeleteLocalRef(jsStr);
        }
        env->DeleteLocalRef(cls);
    }
}

/**
 * JNI接口
 */
extern "C" {

static constexpr float kSpeedStep = 0.5f;
static constexpr float kSpeedMin  = 0.1f;
static constexpr float kSpeedMax  = 10.0f;

JNIEXPORT void JNICALL
Java_com_ray_snxyjde_NativeLib_callBoost(JNIEnv *env, jclass) {
    std::lock_guard<std::mutex> lock(g_speed_mutex);
    g_current_speed += kSpeedStep;
    if (g_current_speed > kSpeedMax) g_current_speed = kSpeedMax;
    LOG("Speed: %.1fx", g_current_speed);
    apply_speed(env, g_current_speed);
}

JNIEXPORT void JNICALL
Java_com_ray_snxyjde_NativeLib_callSlowdown(JNIEnv *env, jclass) {
    std::lock_guard<std::mutex> lock(g_speed_mutex);
    g_current_speed -= kSpeedStep;
    if (g_current_speed < kSpeedMin) g_current_speed = kSpeedMin;
    LOG("Speed: %.1fx", g_current_speed);
    apply_speed(env, g_current_speed);
}

JNIEXPORT jfloat JNICALL
Java_com_ray_snxyjde_NativeLib_getCurrentSpeed(JNIEnv *, jclass) {
    return g_current_speed;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *, void *) {
    LOG("libmyde.so loaded");
    return JNI_VERSION_1_6;
}

}