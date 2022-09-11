#include "hash-functions.h"

namespace rncryptopp::hash {

void hash(jsi::Runtime &rt, CppArgs *args, std::string *result) {
  if (args->size() != 3)
    throwJSError(rt, "RNCryptopp: hash invalid number of arguments");

  QuickValue data = args->at(2);
  if (!isDataStringOrAB(data))
    throwJSError(rt, "RNCryptopp: hash data is not a string or ArrayBuffer");

  std::string hash_type = args->at(1).stringValue;
  if (hash_type == "SipHash_2_4_64") {
    SipHash<2, 4, false> hash;
    StringSource(data.stringValue, true,
                 new HashFilter(hash, new HexEncoder(new StringSink(*result))));
    return;
  } else if (hash_type == "SipHash_4_8_128") {
    SipHash<4, 8, true> hash;
    StringSource(data.stringValue, true,
                 new HashFilter(hash, new HexEncoder(new StringSink(*result))));
    return;
  } else if (hash_type == "CRC32") {
    CRC32 hash;
    word32 digest = 0;
    hash.CalculateDigest(
        reinterpret_cast<CryptoPP::byte *>(&digest),
        reinterpret_cast<CryptoPP::byte const *>(data.stringValue.data()),
        data.stringValue.size());
    std::stringstream ss;
    ss << std::hex << digest;
    *result = ss.str();
    return;
  } else {
    auto hasResult = invokeWithHash<rncryptopp::hash::calculate_hash>()(
        hash_type, &data.stringValue, result);
    if (!hasResult)
      throwJSError(rt, "RNCryptopp: hash - invalid hash name.");
  }
}
} // namespace rncryptopp::hash
