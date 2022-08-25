import React from 'react';

import { Text } from 'react-native';
import Cryptopp from 'react-native-cryptopp';

export const KeyDerivation = () => {
  const HKDF = Cryptopp.keyDerivation.HKDF(
    'password',
    'salt',
    'HKDF key derivation',
    'BLAKE2b'
  );

  const PKCS12_PBKDF = Cryptopp.keyDerivation.PKCS12_PBKDF(
    'password',
    'salt',
    'SHA256',
    1024
  );

  const PKCS5_PBKDF1 = Cryptopp.keyDerivation.PKCS5_PBKDF1(
    'password',
    'salt',
    'SHA256',
    1024
  );

  const PKCS5_PBKDF2 = Cryptopp.keyDerivation.PKCS5_PBKDF2(
    'password',
    'salt',
    'SHA256',
    1024
  );

  const Scrypt = Cryptopp.keyDerivation.Scrypt(
    'password',
    'NaCl',
    1024,
    8,
    16,
    64
  );
  return (
    <>
      <Text testID={`HKDF`}>{HKDF}</Text>
      <Text testID={`PKCS12_PBKDF`}>{PKCS12_PBKDF}</Text>
      <Text testID={`PKCS5_PBKDF1`}>{PKCS5_PBKDF1}</Text>
      <Text testID={`PKCS5_PBKDF2`}>{PKCS5_PBKDF2}</Text>
      <Text testID={`Scrypt`}>{Scrypt}</Text>
    </>
  );
};

