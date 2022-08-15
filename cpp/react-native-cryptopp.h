#pragma once

#include <ReactCommon/CallInvoker.h>
#include <jsi/jsi.h>
#include <jsi/jsilib.h>

#include "JSIHelper.h"
#include "ThreadPool.h"
#include "aes-candidates.hpp"
#include "hash-functions-ho.h"
#include "hash-functions.h"
#include "helpers.h"
#include "insecure.h"
#include "key-derivation.h"
#include "message-authentication.h"
#include "public-key.h"
#include "utils.h"

using namespace facebook;
using namespace rncryptopp;
using namespace rncryptopp::jsiHelper;

void rncryptopp_install(jsi::Runtime &jsiRuntime,
                        std::shared_ptr<react::CallInvoker> jsCallInvoker);
