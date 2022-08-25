import React from 'react';

import { Text } from 'react-native';
import Cryptopp from 'react-native-cryptopp';

const HMAC_TEXT = 'HMAC Test';
const HMAC_TEXT_AB = Cryptopp.utils.stringToBytes(HMAC_TEXT);
const HMAC_KEY = '11A47EC4465DD95FCD393075E7D3C4EB';
const HMAC_KEY_AB = Cryptopp.utils.stringToBytes(HMAC_KEY, "hex");

const CMAC_TEXT = 'CMAC Test';
const CMAC_TEXT_AB = Cryptopp.utils.stringToBytes(CMAC_TEXT);
const CMAC_KEY = 'B8B34DA2D4C4D578D8494390E3DFE7A7';
const CMAC_KEY_AB = Cryptopp.utils.stringToBytes(CMAC_KEY, "hex");

export const MessageAuthentication = () => {
  const HMAC_generate = Cryptopp.HMAC.generate(HMAC_TEXT, HMAC_KEY, 'SHA256');

  const HMAC_verify = Cryptopp.HMAC.verify(
    HMAC_TEXT,
    HMAC_KEY,
    'SHA256',
    HMAC_generate
  );

  const HMAC_generate_ab = Cryptopp.HMAC.generate(
    HMAC_TEXT_AB,
    HMAC_KEY,
    'SHA256'
  );

  const HMAC_verify_ab = Cryptopp.HMAC.verify(
    HMAC_TEXT_AB,
    HMAC_KEY,
    'SHA256',
    HMAC_generate_ab
  );

  const HMAC_generate_ab2 = Cryptopp.HMAC.generate(
    HMAC_TEXT_AB,
    HMAC_KEY_AB,
    'SHA256'
  );

  const HMAC_verify_ab2 = Cryptopp.HMAC.verify(
    HMAC_TEXT_AB,
    HMAC_KEY_AB,
    'SHA256',
    HMAC_generate_ab2
  );

  const CMAC_generate = Cryptopp.CMAC.generate(CMAC_TEXT, CMAC_KEY, 'AES');

  const CMAC_verify = Cryptopp.CMAC.verify(
    CMAC_TEXT,
    CMAC_KEY,
    'AES',
    CMAC_generate
  );

  const CMAC_generate_ab = Cryptopp.CMAC.generate(
    CMAC_TEXT_AB,
    CMAC_KEY,
    'AES'
  );

  const CMAC_verify_ab = Cryptopp.CMAC.verify(
    CMAC_TEXT_AB,
    CMAC_KEY,
    'AES',
    CMAC_generate_ab
  );

  const CMAC_generate_ab2 = Cryptopp.CMAC.generate(
    CMAC_TEXT_AB,
    CMAC_KEY_AB,
    'AES'
  );

  const CMAC_verify_ab2 = Cryptopp.CMAC.verify(
    CMAC_TEXT_AB,
    CMAC_KEY_AB,
    'AES',
    CMAC_generate_ab2
  );

  return (
    <>
      {/* HMAC */}
      <Text testID={`HMAC_generate`}>{HMAC_generate}</Text>
      <Text testID={`HMAC_verify`}>{HMAC_verify ? 'true' : 'false'}</Text>
      <Text testID={`HMAC_generate_ab`}>{Cryptopp.utils.toHex(HMAC_generate_ab)}</Text>
      <Text testID={`HMAC_verify_ab`}>{HMAC_verify_ab ? 'true' : 'false'}</Text>
      <Text testID={`HMAC_generate_ab2`}>{Cryptopp.utils.toHex(HMAC_generate_ab2)}</Text>
      <Text testID={`HMAC_verify_ab2`}>
        {HMAC_verify_ab2 ? 'true' : 'false'}
      </Text>
      {/* CMAC */}
      <Text testID={`CMAC_generate`}>{CMAC_generate}</Text>
      <Text testID={`CMAC_verify`}>{CMAC_verify ? 'true' : 'false'}</Text>
      <Text testID={`CMAC_generate_ab`}>{Cryptopp.utils.toHex(CMAC_generate_ab)}</Text>
      <Text testID={`CMAC_verify_ab`}>{CMAC_verify_ab ? 'true' : 'false'}</Text>
      <Text testID={`CMAC_generate_ab2`}>{Cryptopp.utils.toHex(CMAC_generate_ab2)}</Text>
      <Text testID={`CMAC_verify_ab2`}>
        {CMAC_verify_ab2 ? 'true' : 'false'}
      </Text>
    </>
  );
};

