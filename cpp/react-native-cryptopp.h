#ifndef REACT_NATIVE_CRYPTOPP_H
#define REACT_NATIVE_CRYPTOPP_H

#include <jsi/jsilib.h>
#include <jsi/jsi.h>

#include "hash-functions.h"
#include "aes-candidates.h"
#include "insecure.h"
#include "key-derivation.h"
#include "utils.h"
#include "helpers.h"

using namespace facebook;

void rncryptopp_install(jsi::Runtime &jsiRuntime);

void rncryptopp_cleanup();

#endif /* REACT_NATIVE_CRYPTOPP_H */
