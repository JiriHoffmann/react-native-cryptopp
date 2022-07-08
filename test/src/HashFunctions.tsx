import React from 'react';

import { Text } from 'react-native';
import Cryptopp from 'react-native-cryptopp';

const msg = 'Yoda said, Do or do not. There is no try.';
const lsh_msg = 'abc';

export const HashFunctions = () => {
  return (
    <>
      <Text testID="BLAKE2b">{Cryptopp.hashFunctions.BLAKE2b(msg)}</Text>
      <Text testID="BLAKE2s">{Cryptopp.hashFunctions.BLAKE2s(msg)}</Text>
      <Text testID="Keccak_224">
        {Cryptopp.hashFunctions.Keccak(msg, '224')}
      </Text>
      <Text testID="Keccak_256">
        {Cryptopp.hashFunctions.Keccak(msg, '256')}
      </Text>
      <Text testID="Keccak_384">
        {Cryptopp.hashFunctions.Keccak(msg, '384')}
      </Text>
      <Text testID="Keccak_512">
        {Cryptopp.hashFunctions.Keccak(msg, '512')}
      </Text>
      <Text testID="SHA1">{Cryptopp.hashFunctions.SHA1(msg)}</Text>
      <Text testID="SHA224">{Cryptopp.hashFunctions.SHA2(msg, '224')}</Text>
      <Text testID="SHA256">{Cryptopp.hashFunctions.SHA2(msg, '256')}</Text>
      <Text testID="SHA384">{Cryptopp.hashFunctions.SHA2(msg, '384')}</Text>
      <Text testID="SHA512">{Cryptopp.hashFunctions.SHA2(msg, '512')}</Text>
      <Text testID="SHA3_224">{Cryptopp.hashFunctions.SHA3(msg, '224')}</Text>
      <Text testID="SHA3_256">{Cryptopp.hashFunctions.SHA3(msg, '256')}</Text>
      <Text testID="SHA3_384">{Cryptopp.hashFunctions.SHA3(msg, '384')}</Text>
      <Text testID="SHA3_512">{Cryptopp.hashFunctions.SHA3(msg, '512')}</Text>
      <Text testID="SHAKE128">{Cryptopp.hashFunctions.SHAKE(msg, '128')}</Text>
      <Text testID="SHAKE256">{Cryptopp.hashFunctions.SHAKE(msg, '256')}</Text>
      <Text testID="SM3">{Cryptopp.hashFunctions.SM3(msg)}</Text>
      <Text testID="Tiger">{Cryptopp.hashFunctions.Tiger(msg)}</Text>
      <Text testID="RIPEMD128">
        {Cryptopp.hashFunctions.RIPEMD(msg, '128')}
      </Text>
      <Text testID="RIPEMD160">
        {Cryptopp.hashFunctions.RIPEMD(msg, '160')}
      </Text>
      <Text testID="RIPEMD256">
        {Cryptopp.hashFunctions.RIPEMD(msg, '256')}
      </Text>
      <Text testID="RIPEMD320">
        {Cryptopp.hashFunctions.RIPEMD(msg, '320')}
      </Text>

      {/* LSH functions have a different input */}
      <Text testID="LSH224">{Cryptopp.hashFunctions.LSH(lsh_msg, '224')}</Text>
      <Text testID="LSH256">{Cryptopp.hashFunctions.LSH(lsh_msg, '256')}</Text>
      <Text testID="LSH384">{Cryptopp.hashFunctions.LSH(lsh_msg, '384')}</Text>
      <Text testID="LSH512">{Cryptopp.hashFunctions.LSH(lsh_msg, '512')}</Text>
    </>
  );
};
