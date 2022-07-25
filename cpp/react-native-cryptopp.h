#pragma once

#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "aes-candidates.hpp"
#include "hash-functions.h"
#include "helpers.h"
#include "host_objects/hash-functions.h"
#include "insecure.h"
#include "key-derivation.h"
#include "message-authentication.h"
#include "public-key.h"
#include "utils.h"

using namespace facebook;

void rncryptopp_install(jsi::Runtime &jsiRuntime);
