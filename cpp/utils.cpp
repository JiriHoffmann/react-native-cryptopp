#include "utils.h"

namespace rncryptopp::utils {
void toBase64(jsi::Runtime &rt, CppArgs *args, std::string *target,
              StringEncoding *targetEncoding) {
  if (args->size() < 2)
    throwJSError(rt, "RNCryptopp: toBase64 invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throw jsi::JSError(
        rt, "RNCryptopp: toBase64 data is not a string or ArrayBuffer");
  auto inputEncoding = getEncodingFromArgs(rt, args, 2);
  decodeJSIString(args->at(1), target, inputEncoding);
  *targetEncoding = ENCODING_BASE64;
}

void toBase64Url(jsi::Runtime &rt, CppArgs *args, std::string *target,
                 StringEncoding *targetEncoding) {
  if (args->size() < 2)
    throwJSError(rt, "RNCryptopp: toBase64Url invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throw jsi::JSError(
        rt, "RNCryptopp: toBase64Url data is not a string or ArrayBuffer");
  auto inputEncoding = getEncodingFromArgs(rt, args, 2);
  decodeJSIString(args->at(1), target, inputEncoding);
  *targetEncoding = ENCODING_BASE64URL;
}

void toHex(jsi::Runtime &rt, CppArgs *args, std::string *target,
           StringEncoding *targetEncoding) {
  if (args->size() < 2)
    throwJSError(rt, "RNCryptopp: toHex invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throw jsi::JSError(rt,
                       "RNCryptopp: toHex data is not a string or ArrayBuffer");
  auto inputEncoding = getEncodingFromArgs(rt, args, 2);
  decodeJSIString(args->at(1), target, inputEncoding);
  *targetEncoding = ENCODING_HEX;
}

void toUtf8(jsi::Runtime &rt, CppArgs *args, std::string *target,
            StringEncoding *targetEncoding) {
  if (args->size() < 2)
    throwJSError(rt, "RNCryptopp: toUtf8 invalid number of arguments");

  if (!isDataStringOrAB(args->at(1)))
    throw jsi::JSError(
        rt, "RNCryptopp: toUtf8 data is not a string or ArrayBuffer");
  auto inputEncoding = getEncodingFromArgs(rt, args, 2);
  decodeJSIString(args->at(1), target, inputEncoding);
  *targetEncoding = ENCODING_UTF8;
}

void randomBytes(jsi::Runtime &rt, CppArgs *args, std::string *target,
                 QuickDataType *targetType) {
  if (args->size() != 2)
    throwJSError(rt, "RNCryptopp: randomBytes invalid number of arguments");

  if (!isDataInteger(args->at(1)))
    throwJSError(rt, "RNCryptopp: randomBytes size is not a number");
  int size = (int)args->at(1).doubleOrIntValue;

  AutoSeededRandomPool prng;
  SecByteBlock random(size);
  prng.GenerateBlock(random, random.size());

  *target = std::string((const char *)random.data(), random.size());
  *targetType = ARRAY_BUFFER;
}

void stringToBytes(jsi::Runtime &rt, CppArgs *args, std::string *target,
                   QuickDataType *targetType) {
  if (args->size() < 2)
    throwJSError(rt, "RNCryptopp: stringToBytes invalid number of arguments");

  if (!isDataString(args->at(1)))
    throw jsi::JSError(rt, "RNCryptopp: stringToBytes data is not a string");

  std::string decoded;
  auto encoding = rncryptopp::getEncodingFromArgs(rt, args, 2);
  decodeJSIString(args->at(1), target, encoding);
  *targetType = ARRAY_BUFFER;
}
} // namespace rncryptopp::utils
