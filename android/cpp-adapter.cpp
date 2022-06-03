#include <jni.h>
#include "react-native-cryptopp.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativecryptopp_CryptoppModule_initialize(JNIEnv* env, jclass clazz, jlong jsiPtr,
                                                       jstring doc_dir) {
  rncryptopp_install(*reinterpret_cast<facebook::jsi::Runtime*>(jsiPtr));
}
