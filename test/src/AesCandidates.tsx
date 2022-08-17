import React from 'react';

import { Text } from 'react-native';
import Cryptopp from 'react-native-cryptopp';

const msg = 'CBC Mode Test';
const msg_ab = Cryptopp.utils.stringToBytes(msg);
const AES_KEY = Cryptopp.utils.stringToBytes(
  '01AAD7DB7831A398088EBBA9A3C85546',
  'hex'
)
const AES_IV = Cryptopp.utils.stringToBytes('13BB6FCB744663EC2A9EF711FA934BAA', 'hex')

const standards = [
  {
    name: 'RC6',
    key: Cryptopp.utils.stringToBytes(
      '62A4A0234EE404102848A3E914B76BEE',
      'hex'
    ),
    iv: Cryptopp.utils.stringToBytes('E49B294B0FD7A18C22EBDE4C0C8DDD56', 'hex'),
  },
  {
    name: 'Twofish',
    key: Cryptopp.utils.stringToBytes(
      '6B990E620635B4C36A1B737487CEAD8D',
      'hex'
    ),
    iv: Cryptopp.utils.stringToBytes('05C9428085EE3F34D7ECE73C5628F605', 'hex'),
  },
] as const;
const modes = [
  'cbc', 
  'cfb',
  'ctr',
  'ecb',
  'ofb',
] as const;

export const AesCandidates = () => {
  const aes_encrypted_ab = Cryptopp.AES.encrypt(
    msg_ab,
    AES_KEY,
    AES_IV,
    'cbc',
    'hex'
  );
  const aes_decrypted_ab = Cryptopp.AES.decrypt(
    aes_encrypted_ab,
    AES_KEY,
    AES_IV,
    'cbc',
    'hex'
  );

  const aes_encrypted_b64 = Cryptopp.AES.encrypt(msg, AES_KEY, AES_IV, 'cbc');
  const aes_decrypted_b64 = Cryptopp.AES.decrypt(
    aes_encrypted_b64,
    AES_KEY,
    AES_IV,
    'cbc'
  );

  return (
    <>
      {/*   Encryption & decryption */}
      {modes.map((mode) => {
        return (
          <Text testID={`AES_${mode}_encrypted`}>
            {Cryptopp.AES.encrypt(msg, AES_KEY, AES_IV, mode, 'hex')}
          </Text>
        );
      })}
      {standards.map((standard) => {
        const encrypted = Cryptopp[standard.name].encrypt(
          msg,
          standard.key,
          standard.iv,
          'cbc',
          'hex'
        );
        const decrypted = Cryptopp[standard.name].decrypt(
          encrypted,
          standard.key,
          standard.iv,
          'cbc',
          'hex'
        );

        return (
          <>
            <Text testID={`${standard.name}_cbc_encrypted`}>{encrypted}</Text>
            <Text testID={`${standard.name}_cbc_decrypted`}>{decrypted}</Text>
          </>
        );
      })}

      {/*   ArrayBuffers  */}
      <Text testID={`AES_encrypted_ab`}>
        {Cryptopp.utils.toHex(aes_encrypted_ab)}
      </Text>
      <Text testID={`AES_decrypted_ab`}>
        {Cryptopp.utils.toUtf8(aes_decrypted_ab)}
      </Text>

      {/*   Base64  */}
      <Text testID={`AES_encrypted_b64`}>{aes_encrypted_b64}</Text>
      <Text testID={`AES_decrypted_b64`}>{aes_decrypted_b64}</Text>
    </>
  );
};

