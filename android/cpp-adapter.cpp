#include <jni.h>
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <ReactCommon/CallInvokerHolder.h>
#include "react-native-cryptopp.h"

struct CryptoppBridge : jni::JavaClass<CryptoppBridge>
{
  static constexpr auto kJavaDescriptor = "Lcom/reactnativecryptopp/CryptoppBridge;";

  static void registerNatives()
  {
    javaClassStatic()->registerNatives({// initialization for JSI
                                        makeNativeMethod("installNativeJsi", CryptoppBridge::installNativeJsi)});
  }

private:
  static void installNativeJsi(jni::alias_ref<jni::JObject> thiz,
                               jlong jsiRuntimePtr,
                               jni::alias_ref<react::CallInvokerHolder::javaobject> jsCallInvokerHolder)
  {
    auto jsiRuntime = reinterpret_cast<jsi::Runtime *>(jsiRuntimePtr);
    auto jsCallInvoker = jsCallInvokerHolder->cthis()->getCallInvoker();

    rncryptopp_install(*jsiRuntime, jsCallInvoker);
  }
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *)
{
  return jni::initialize(vm, []
                         { CryptoppBridge::registerNatives(); });
}