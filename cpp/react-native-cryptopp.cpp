#import "react-native-cryptopp.h"

#include <iostream>
#include <sstream>

using namespace facebook;

namespace cryptopp
{
  void install(jsi::Runtime& jsiRuntime) {

    auto multiply = jsi::Function::createFromHostFunction(
        jsiRuntime,
        jsi::PropNameID::forAscii(jsiRuntime, "multiply"),
        2, 
        [](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* args, size_t count) -> jsi::Value {
          double a = args[0].asNumber();
  		double b = args[1].asNumber();

          return jsi::Value(a*b);
        }
    );

    jsi::Object module = jsi::Object(jsiRuntime);
    module.setProperty(jsiRuntime, "multiply", std::move(multiply));

    jsiRuntime.global().setProperty(jsiRuntime, "cryptoppModule", std::move(module));
  }

  void cleanup() {
  }
}