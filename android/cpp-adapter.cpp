#include <jni.h>
#include "react-native-cryptopp.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativecryptopp_CryptoppModule_initialize(JNIEnv* env, jclass clazz, jlong jsiPtr) {
  cryptopp::install(*reinterpret_cast<facebook::jsi::Runtime*>(jsiPtr));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativecryptopp_CryptoppModul_destruct(JNIEnv* env, jclass clazz) {
  cryptopp::cleanup();
}
