import React from 'react';

import { Text } from 'react-native';
import Cryptopp from 'react-native-cryptopp';

const msg = 'Yoda said, Do or do not. There is no try.';
const msg_p = 'Yoda said, Do or do |not. There is no try.';
const lsh_msg = 'abc';

export const HashFunctions = () => {
  const hash = Cryptopp.hash.create('BLAKE2b');
  const hash_ab = Cryptopp.hash.create('BLAKE2b');

  const chunks = msg_p.split('|');
  chunks.forEach(chunk => hash.update(chunk));
  chunks.forEach(chunk => hash_ab.update(Cryptopp.utils.stringToBytes(chunk)))

  const BLAKE2_progressive = hash.finalize();
  const BLAKE2_progressive_ab = hash_ab.finalize();

  return (
    <>
      <Text testID="BLAKE2b">{Cryptopp.hash.BLAKE2b(msg)}</Text>
      <Text testID="BLAKE2_progressive">{BLAKE2_progressive}</Text>
      <Text testID="BLAKE2_progressive_ab">{BLAKE2_progressive_ab}</Text>
      <Text testID="BLAKE2s">{Cryptopp.hash.BLAKE2s(msg)}</Text>
      <Text testID="Keccak224">{Cryptopp.hash.Keccak224(msg)}</Text>
      <Text testID="Keccak256">{Cryptopp.hash.Keccak256(msg)}</Text>
      <Text testID="Keccak384">{Cryptopp.hash.Keccak384(msg)}</Text>
      <Text testID="Keccak512">{Cryptopp.hash.Keccak512(msg)}</Text>
      <Text testID="SHA1">{Cryptopp.hash.SHA1(msg)}</Text>
      <Text testID="SHA224">{Cryptopp.hash.SHA224(msg)}</Text>
      <Text testID="SHA256">{Cryptopp.hash.SHA256(msg)}</Text>
      <Text testID="SHA384">{Cryptopp.hash.SHA384(msg)}</Text>
      <Text testID="SHA512">{Cryptopp.hash.SHA512(msg)}</Text>
      <Text testID="SHA3_224">{Cryptopp.hash.SHA3_224(msg)}</Text>
      <Text testID="SHA3_256">{Cryptopp.hash.SHA3_256(msg)}</Text>
      <Text testID="SHA3_384">{Cryptopp.hash.SHA3_384(msg)}</Text>
      <Text testID="SHA3_512">{Cryptopp.hash.SHA3_512(msg)}</Text>
      <Text testID="SHAKE128">{Cryptopp.hash.SHAKE128(msg)}</Text>
      <Text testID="SHAKE256">{Cryptopp.hash.SHAKE256(msg)}</Text>
      <Text testID="SM3">{Cryptopp.hash.SM3(msg)}</Text>
      <Text testID="Tiger">{Cryptopp.hash.Tiger(msg)}</Text>
      <Text testID="RIPEMD128">{Cryptopp.hash.RIPEMD128(msg)}</Text>
      <Text testID="RIPEMD160">{Cryptopp.hash.RIPEMD160(msg)}</Text>
      <Text testID="RIPEMD256">{Cryptopp.hash.RIPEMD256(msg)}</Text>
      <Text testID="RIPEMD320">{Cryptopp.hash.RIPEMD320(msg)}</Text>

      {/* LSH functions have a different input */}
      <Text testID="LSH224">{Cryptopp.hash.LSH224(lsh_msg)}</Text>
      <Text testID="LSH256">{Cryptopp.hash.LSH256(lsh_msg)}</Text>
      <Text testID="LSH384">{Cryptopp.hash.LSH384(lsh_msg)}</Text>
      <Text testID="LSH512">{Cryptopp.hash.LSH512(lsh_msg)}</Text>
    </>
  );
};
