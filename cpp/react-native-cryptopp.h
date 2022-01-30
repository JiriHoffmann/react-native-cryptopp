#ifndef REACT_NATIVE_CRYPTOPP_H
#define REACT_NATIVE_CRYPTOPP_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

namespace cryptopp
{

  void install(facebook::jsi::Runtime &jsiRuntime);
  void cleanup();
}

#endif /* REACT_NATIVE_CRYPTOPP_H */