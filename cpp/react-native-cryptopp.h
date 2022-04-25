#ifndef REACT_NATIVE_CRYPTOPP_H
#define REACT_NATIVE_CRYPTOPP_H

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "cryptopp/osrng.h"

#include "aes-candidates.h"
#include "hash-functions.h"
#include "helpers.h"
#include "insecure.h"
#include "key-derivation.h"
#include "message-authentication.h"
#include "public-key.h"
#include "utils.h"

using namespace facebook;

void rncryptopp_install(jsi::Runtime &jsiRuntime);

void rncryptopp_cleanup();

#endif /* REACT_NATIVE_CRYPTOPP_H */
