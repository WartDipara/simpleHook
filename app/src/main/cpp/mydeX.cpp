#define K129 "if(this.animationMgr&&this.animationMgr.__originUpdate){this.animationMgr.__originUpdate(0);}else if(this.animationMgr&&this.animationMgr.update){this.animationMgr.update(0);}"
#define K128 "if(this.actionMgr&&this.actionMgr.__originUpdate){this.actionMgr.__originUpdate(0);}else if(this.actionMgr&&this.actionMgr.update){this.actionMgr.update(0);}"
#define K127 "if(this.tweenSys&&this.tweenSys.__originUpdate){this.tweenSys.__originUpdate(0);}else if(this.tweenSys&&this.tweenSys.update){this.tweenSys.update(0);}"
#define K126 "if(ccGlobal.Animation&&ccGlobal.Animation.prototype&&!ccGlobal.Animation.prototype.__speedHackPatched&&ccGlobal.Animation.prototype.update){"
#define K125 "if(scheduler&&scheduler.__originUpdate){scheduler.__originUpdate(0);}else if(scheduler&&scheduler.update){scheduler.update(0);}"
#define K124 "if(window.sp&&sp.Skeleton&&sp.Skeleton.prototype&&!sp.Skeleton.prototype.__speedHackPatched&&sp.Skeleton.prototype.update){"
#define K123 "var animationMgr=director.getAnimationManager?director.getAnimationManager():director._animationManager;"
#define K122 "var actionMgr=director.getActionManager?director.getActionManager():director._actionManager;"
#define K121 "if(ccGlobal.Node&&ccGlobal.Node.prototype&&!ccGlobal.Node.prototype.__speedHackPatched){"
#define K120 LOG("SpeedHack: symbol %s resolved -> target=%p, replace=%p", symbol, target, replace);
#define K11F jmethodID method = env->GetStaticMethodID(cls, "executeLua", "(Ljava/lang/String;)V");
#define K11E "}catch(e){console&&console.warn&&console.warn('SpeedHack flush animation error',e);}"
#define K11D "}catch(e){console&&console.warn&&console.warn('SpeedHack flush scheduler error',e);}"
#define K11C "}catch(e){console&&console.warn&&console.warn('SpeedHack flush action error',e);}"
#define K11B "var scheduler=director.getScheduler?director.getScheduler():director._scheduler;"
#define K11A "}catch(e){console&&console.warn&&console.warn('SpeedHack flush delta error',e);}"
#define K119 "}catch(e){console&&console.warn&&console.warn('SpeedHack flush tween error',e);}"
#define K118 "ccGlobal.Animation.prototype.__originUpdate=ccGlobal.Animation.prototype.update;"
#define K117 "var scheduler=this.scheduler||(director.getScheduler&&director.getScheduler());"
#define K116 "director.__originCalculateDeltaTime=director.calculateDeltaTime.bind(director);"
#define K115 "s=(d&&d.getScheduler)?d.getScheduler():((d&&d._scheduler)?d._scheduler:null);"
#define K114 "if(window.console&&console.error){console.error('SpeedHack apply failed',e);}"
#define K113 "if(this.setTimeScale){this.setTimeScale(scale);}else{this.timeScale=scale;}"
#define K112 "return this.__originUpdate.call(this,dt*((window.__GLOBAL_TIME_SCALE)||1));"
#define K111 "if(animationMgr&&!animationMgr.__speedHackPatched&&animationMgr.update){"
#define K110 "}else if(director._compScheduler&&director._compScheduler._tweenSystem){"
#define K10F "var now=(performance&&performance.now)?performance.now():Date.now();"
#define K10E "animationMgr.__originUpdate=animationMgr.update.bind(animationMgr);"
#define K10D "sp.Skeleton.prototype.__originUpdate=sp.Skeleton.prototype.update;"
#define K10C "return this.__originalUpdate(dt*(window.__GLOBAL_TIME_SCALE||1));"
#define K10B "if(!GameLogicManager.__originalUpdate&&GameLogicManager.update){"
#define K10A LOG("SpeedHack: hook %s success, original=%p", symbol, *original);
#define K109 "if(actionMgr&&!actionMgr.__speedHackPatched&&actionMgr.update){"
#define K108 "if(scheduler&&!scheduler.__speedHackPatched&&scheduler.update){"
#define K107 "if(!director.__speedHackPatched&&director.calculateDeltaTime){"
#define K106 "if(tweenSys&&!tweenSys.__speedHackPatched&&tweenSys.update){"
#define K105 "GameLogicManager.__originalUpdate=GameLogicManager.update;"
#define K104 "actionMgr.__originUpdate=actionMgr.update.bind(actionMgr);"
#define K103 "scheduler.__originUpdate=scheduler.update.bind(scheduler);"
#define K102 "if(ccGlobal.TweenSystem&&ccGlobal.TweenSystem.instance){"
#define K101 jclass cls = env->FindClass("com/ray/snxyjde/SpeedUtil");
#define K100 "tweenSys.__originUpdate=tweenSys.update.bind(tweenSys);"
#define KFF hook_symbol("_ZN5spine22SkeletonCacheAnimation6updateEf",
#define KFE "}else if(typeof this.tweenSys.timeScale!=='undefined'){"
#define KFD LOG("SpeedHack: native speed set %.3f", g_native_speed);
#define KFC "ccGlobal.Animation.prototype.__speedHackPatched=true;"
#define KFB LOG("SpeedHack: hook %s failed, ret=%d", symbol, ret);
#define KFA "var originGet=ccGlobal.Node.prototype.getScheduler;"
#define KF9 "this.__originUpdate(dt*(this.__speedHackScale||1));"
#define KF8 Java_com_ray_snxyjde_NativeLib_getCurrentSpeed(JNIEnv
#define KF7 hook_symbol("_ZN5spine17SkeletonAnimation6updateEf",
#define KF6 "setTimeout(function(){self.setScale(scale);},100);"
#define KF5 "ccGlobal.Animation.prototype.update=function(dt){"
#define KF4 "if(!ccGlobal||!ccGlobal.director){return false;}"
#define KF3 Java_com_ray_snxyjde_NativeLib_callSlowdown(JNIEnv
#define KF2 "ccGlobal.Node.prototype.__speedHackPatched=true;"
#define KF1 "ccGlobal.Node.prototype.getScheduler=function(){"
#define KF0 hook_symbol("_ZN5spine14AnimationState6updateEf",
#define KEF "tweenSys=director._compScheduler._tweenSystem;"
#define KEE "scheduler.__speedHackSetScale=function(scale){"
#define KED "sp.Skeleton.prototype.__speedHackPatched=true;"
#define KEC Java_com_ray_snxyjde_NativeLib_callBoost(JNIEnv
#define KEB LOG("SpeedHack: symbol %s not found", symbol);
#define KEA hook_symbol("_ZN5spine10TrackEntry6updateEf",
#define KE9 "if(window.CacheAsset&&CacheAsset.Instance){"
#define KE8 "director.calculateDeltaTime=function(now){"
#define KE7 "this._deltaTime*=this.__speedHackScale||1;"
#define KE6 "this.scheduler.__speedHackSetScale(scale);"
#define KE5 "var s=originGet?originGet.call(this):null;"
#define KE4 "sp.Skeleton.prototype.update=function(dt){"
#define KE3 "CacheAsset.Instance.fightSpeedRate=scale;"
#define KE2 "director.__originCalculateDeltaTime(now);"
#define KE1 "this.animationMgr.__speedHackScale=scale;"
#define KE0 "if(director.__originCalculateDeltaTime){"
#define KDF (void*)SkeletonCacheAnimation_update_hook,
#define KDE "tweenSys=ccGlobal.TweenSystem.instance;"
#define KDD "if(this.scheduler.__speedHackSetScale){"
#define KDC "this.animationMgr.setTimeScale(scale);"
#define KDB "this.scheduler.__speedHackScale=scale;"
#define KDA "if(GameLogicManager.__originalUpdate){"
#define KD9 "}else if(this.scheduler.setTimeScale){"
#define KD8 (void**)&g_origSkeletonAnimationUpdate);
#define KD7 SkeletonCacheAnimation_update_hook(void*
#define KD6 "this.actionMgr.__speedHackScale=scale;"
#define KD5 "this.__originCalculateDeltaTime(now);"
#define KD4 "this.tweenSys.__speedHackScale=scale;"
#define KD3 "this.director.__speedHackScale=scale;"
#define KD2 "GameLogicManager.update=function(dt){"
#define KD1 "animationMgr.__speedHackPatched=true;"
#define KD0 "CacheAsset.Instance.fightSpeed=scale;"
#define KCF (void**)&g_origAnimationStateUpdate);
#define KCE "window.__SpeedHack.setScale(scale);"
#define KCD (void*)SkeletonAnimation_update_hook,
#define KCC LOG("Speed: %.1fx", g_current_speed);
#define KCB "this.actionMgr.setTimeScale(scale);"
#define KCA "this.scheduler.setTimeScale(scale);"
#define KC9 "if(this.animationMgr.setTimeScale){"
#define KC8 "scheduler.__speedHackPatched=true;"
#define KC7 "this.tweenSys.setTimeScale(scale);"
#define KC6 (void**)&g_origSkeletonCacheUpdate);
#define KC5 "}else if(this.actionMgr.setSpeed){"
#define KC4 "actionMgr.__speedHackPatched=true;"
#define KC3 "tweenSys.__speedHackPatched=true;"
#define KC2 "director.__speedHackPatched=true;"
#define KC1 SkeletonAnimation_update_hook(void*
#define KC0 "window.__GLOBAL_TIME_SCALE=scale;"
#define KBF g_origSkeletonAnimationUpdate(self,
#define KBE "animationMgr.update=function(dt){"
#define KBD (void*)AnimationState_update_hook,
#define KBC "if(this.actionMgr.setTimeScale){"
#define KBB "animationMgr.__speedHackScale=1;"
#define KBA "this.scheduler.timeScale=scale;"
#define KB9 "this.animationMgr=animationMgr;"
#define KB8 (void**)&g_origTrackEntryUpdate);
#define KB7 "if(this.tweenSys.setTimeScale){"
#define KB6 "this.actionMgr.setSpeed(scale);"
#define KB5 "var director=ccGlobal.director;"
#define KB4 AnimationState_update_hook(void*
#define KB3 "actionMgr.update=function(dt){"
#define KB2 g_origAnimationStateUpdate(self,
#define KB1 "this.tweenSys.timeScale=scale;"
#define KB0 "scheduler.update=function(dt){"
#define KAF "actionMgr.__speedHackScale=1;"
#define KAE "scheduler.__speedHackScale=1;"
#define KAD "tweenSys.update=function(dt){"
#define KAC g_origSkeletonCacheUpdate(self,
#define KAB (g_origSkeletonAnimationUpdate)
#define KAA "if(window.GameLogicManager){"
#define KA9 "this.__speedHackScale=scale;"
#define KA8 "tweenSys.__speedHackScale=1;"
#define KA7 (void*)TrackEntry_update_hook,
#define KA6 "director.__speedHackScale=1;"
#define KA5 env->CallStaticVoidMethod(cls,
#define KA4 "var director=this.director;"
#define KA3 g_origSkeletonAnimationUpdate
#define KA2 "if(!this.director){return;}"
#define KA1 (g_origAnimationStateUpdate)
#define KA0 g_origTrackEntryUpdate(self,
#define K9F TrackEntry_update_hook(void*
#define K9E "setScale:function(scale){"
#define K9D (g_origSkeletonCacheUpdate)
#define K9C "this.scheduler=scheduler;"
#define K9B std::lock_guard<std::mutex>
#define K9A env->DeleteLocalRef(jsStr);
#define K99 "this.actionMgr=actionMgr;"
#define K98 std::call_once(g_hook_once,
#define K97 g_origAnimationStateUpdate
#define K96 "if(!window.__SpeedHack){"
#define K95 "this.director=director;"
#define K94 g_origSkeletonCacheUpdate
#define K93 "var ccGlobal=window.cc;"
#define K92 "this.tweenSys=tweenSys;"
#define K91 LOG("libmyde.so loaded");
#define K90 env->DeleteLocalRef(cls);
#define K8F "apply:function(scale){"
#define K8E "if(this.animationMgr){"
#define K8D set_native_speed(speed);
#define K8C (g_origTrackEntryUpdate)
#define K8B "if(!director) return;"
#define K8A env->NewStringUTF(js);
#define K89 "if(!this.install()){"
#define K88 "if(!this.installed){"
#define K87 g_origTrackEntryUpdate
#define K86 "window.__SpeedHack={"
#define K85 "this.installed=true;"
#define K84 set_native_speed(float
#define K83 "if(this.actionMgr){"
#define K82 "if(this.scheduler){"
#define K81 install_spine_hooks()
#define K80 install_spine_hooks);
#define K7F "install:function(){"
#define K7E "var d=cc.director;"
#define K7D "if(this.tweenSys){"
#define K7C "var tweenSys=null;"
#define K7B "this.apply(scale);"
#define K7A lock(g_speed_mutex);
#define K79 "animationMgr:null,"
#define K78 "flush:function(){"
#define K77 dlsym(RTLD_DEFAULT,
#define K76 get_scaled_dt(float
#define K75 get_scaled_dt(dt));
#define K74 "installed:false,"
#define K73 apply_speed(JNIEnv
#define K72 DobbyHook(target,
#define K71 g_current_speed);
#define K70 JNI_OnLoad(JavaVM
#define K6F "actionMgr:null,"
#define K6E hook_symbol(const
#define K6D "scheduler:null,"
#define K6C "var scale=%.4f;"
#define K6B JNI_VERSION_1_6;
#define K6A "director:null,"
#define K69 (g_current_speed
#define K68 g_current_speed;
#define K67 apply_speed(env,
#define K66 "var self=this;"
#define K65 "tweenSys:null,"
#define K64 "return false;"
#define K63 g_current_speed
#define K62 g_native_speed;
#define K61 "this.flush();"
#define K60 "(function(){"
#define K5F g_native_speed
#define K5E g_speed_mutex;
#define K5D std::once_flag
#define K5C "return true;"
#define K5B "}catch(e){"
#define K5A g_hook_once;
#define K59 snprintf(js,
#define K58 extern "C" {
#define K57 "return s;"
#define K56 sizeof(js),
#define K55 kSpeedStep;
#define K54 kSpeedMax)
#define K53 kSpeedMin;
#define K52 kSpeedMin)
#define K51 js[16384];
#define K50 std::mutex
#define K4F kSpeedMax;
#define K4E (*)(void*,
#define K4D original);
#define K4C kSpeedStep
#define K4B "if(!s){"
#define K4A (!target)
#define K49 "return;"
#define K48 kSpeedMax
#define K47 constexpr
#define K46 kSpeedMin
#define K45 original)
#define K44 JNIEXPORT
#define K43 UpdateFn
#define K42 "}else{"
#define K41 (method)
#define K40 "})();",
#define K3F nullptr;
#define K3E symbol);
#define K3D replace,
#define K3C symbol,
#define K3B JNICALL
#define K3A method,
#define K39 jclass)
#define K38 speed);
#define K37 jstring
#define K36 jsStr);
#define K35 float);
#define K34 10.0f;
#define K33 "try{"
#define K32 return
#define K31 speed)
#define K30 static
#define K2F scale)
#define K2E void**
#define K2D false;
#define K2C target
#define K2B jfloat
#define K2A scale;
#define K29 0.5f;
#define K28 1.0f;
#define K27 jsStr
#define K26 self,
#define K25 0.1f;
#define K24 *env,
#define K23 char*
#define K22 float
#define K21 (cls)
#define K20 true;
#define K1F using
#define K1E void*
#define K1D scale
#define K1C "},"
#define K1B bool
#define K1A "};"
#define K19 (ret
#define K18 char
#define K17 jint
#define K16 void
#define K15 "}"
#define K14 dt)
#define K13 0.f
#define K12 ret
#define K11 int
#define K10 -=
#define KF +=
#define KE *)
#define KD *,
#define KC if
#define KB !=
#define KA dt
#define K9 <=
#define K8 0)
#define K7 *
#define K6 =
#define K5 >
#define K4 <
#define K3 :
#define K2 ?
#define K1 {
#define K0 }
#include <time.h>
#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <mutex>
#include "dobby.h"
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "SpeedHack", __VA_ARGS__)
#define K12A K30 K22 K63 K6 K28 K30 K22 K5F K6 K28
#define K12B K30 K50 K5E K30 K5D K5A K1F K43 K6 K16
#define K12C K4E K35 K30 K43 K87 K6 K3F K30 K43 K97
#define K12D K6 K3F K30 K43 KA3 K6 K3F K30 K43 K94
#define K12E K6 K3F K30 K22 K76 K14 K1 K32 KA K7
#define K12F K62 K0 K30 K1B K6E K23 K3C K1E K3D K2E
#define K130 K45 K1 K1E K2C K6 K77 K3E KC K4A K1
#define K131 KEB K32 K2D K0 K120 K11 K12 K6 K72 K3D
#define K132 K4D KC K19 KB K8 K1 KFB K32 K2D K0
#define K133 K10A K32 K20 K0 K30 K16 K9F K26 K22 K14
#define K134 K1 KC K8C KA0 K75 K0 K30 K16 KB4 K26
#define K135 K22 K14 K1 KC KA1 KB2 K75 K0 K30 K16
#define K136 KC1 K26 K22 K14 K1 KC KAB KBF K75 K0
#define K137 K30 K16 KD7 K26 K22 K14 K1 KC K9D KAC
#define K138 K75 K0 K30 K16 K81 K1 KEA KA7 KB8 KF0
#define K139 KBD KCF KF7 KCD KD8 KFF KDF KC6 K0 K30
#define K13A K16 K84 K2F K1 K5F K6 K1D K9 K13 K2
#define K13B K13 K3 K2A KFD K0 K30 K16 K73 K24 K22
#define K13C K31 K1 K98 K80 K8D K18 K51 K59 K56 K60
#define K13D K33 K6C K96 K86 K74 K6A K6D K6F K79 K65
#define K13E K7F K93 KF4 KB5 K95 K107 KC2 KA6 K116 KE8
#define K13F KD5 KE7 K1A K15 K11B K108 K9C KC8 KAE K103
#define K140 KB0 KF9 K1A KEE KA9 K113 K1A K15 K122 K109
#define K141 K99 KC4 KAF K104 KB3 KF9 K1A K15 K123 K111
#define K142 KB9 KD1 KBB K10E KBE KF9 K1A K15 K7C K102
#define K143 KDE K110 KEF K15 K106 K92 KC3 KA8 K100 KAD
#define K144 KF9 K1A K15 K124 KED K10D KE4 K112 K1A K15
#define K145 K126 KFC K118 KF5 K112 K1A K15 K121 KF2 KFA
#define K146 KF1 KE5 K4B K7E K115 K15 K57 K1A K15 K85
#define K147 K5C K1C K78 KA4 K8B K33 KE0 K10F KE2 K15
#define K148 K11A K33 K117 K125 K11D K33 K128 K11C K33 K129
#define K149 K11E K33 K127 K119 K1C K8F KA2 KD3 K82 KDD
#define K14A KE6 KD9 KCA K42 KBA KDB K15 K15 K83 KBC
#define K14B KCB KC5 KB6 K42 KD6 K15 K15 K8E KC9 KDC
#define K14C K42 KE1 K15 K15 K7D KB7 KC7 KFE KB1 K15
#define K14D KD4 K15 KC0 KE9 KD0 KE3 K15 KAA K10B K105
#define K14E K15 KDA KD2 K10C K1A K15 K15 K1C K9E K88
#define K14F K89 K66 KF6 K49 K15 K15 K7B K61 K15 K1A
#define K150 K15 KCE K5C K5B K114 K64 K15 K40 K38 K101
#define K151 KC K21 K1 K11F KC K41 K1 K37 K27 K6
#define K152 K8A KA5 K3A K36 K9A K0 K90 K0 K0 K58
#define K153 K30 K47 K22 K4C K6 K29 K30 K47 K22 K46
#define K154 K6 K25 K30 K47 K22 K48 K6 K34 K44 K16
#define K155 K3B KEC K24 K39 K1 K9B K7A K63 KF K55
#define K156 KC K69 K5 K54 K63 K6 K4F KCC K67 K71
#define K157 K0 K44 K16 K3B KF3 K24 K39 K1 K9B K7A
#define K158 K63 K10 K55 KC K69 K4 K52 K63 K6 K53
#define K159 KCC K67 K71 K0 K44 K2B K3B KF8 KD K39
#define K15A K1 K32 K68 K0 K44 K17 K3B K70 KD K16
#define K15B KE K1 K91 K32 K6B K0 K0 
#define K15C K12A K12B K12C K12D K12E K12F K130 K131 K132 K133
#define K15D K134 K135 K136 K137 K138 K139 K13A K13B K13C K13D
#define K15E K13E K13F K140 K141 K142 K143 K144 K145 K146 K147
#define K15F K148 K149 K14A K14B K14C K14D K14E K14F K150 K151
#define K160 K152 K153 K154 K155 K156 K157 K158 K159 K15A K15B
#define K161 K15C K15D K15E K15F K160 
#define K162(__FOX__) __FOX__
K162(K161)
