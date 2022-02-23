#ifndef REACT_NATIVE_CRYPTOPP_H
#define REACT_NATIVE_CRYPTOPP_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "hash-functions.h"
#include "aes-candidates.h"
#include "insecure.h"
#include "utils.h"

using namespace facebook;

namespace rncryptopp {

    void install(jsi::Runtime &jsiRuntime);

    void cleanup();
}

#endif /* REACT_NATIVE_CRYPTOPP_H */
