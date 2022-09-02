import React, { useEffect, useState } from 'react';

import { Text } from 'react-native';
import Cryptopp from 'react-native-cryptopp';

const MESSAGE = 'Secret message';
const rsa_keypair = Cryptopp.RSA.generateKeyPair(2048, 65537);
const rsa_keypair2 = Cryptopp.RSA.generateKeyPair(2048, 65537);

export const PublicKey = () => {
    const [rsa_decrypted_async, set_decrypt_async] = useState("")
    const [rsa_verify_async, set_verify_async] = useState("")
  
    useEffect(()=>{
      const async = async () =>{
        const rsa_encrypted_async = await Cryptopp.async.RSA.encrypt(
            MESSAGE,
            rsa_keypair.public,
            'OAEP_SHA1'
          );
          const rsa_decrypted_async = await Cryptopp.async.RSA.decrypt(
            rsa_encrypted_async,
            rsa_keypair.private,
            'OAEP_SHA1'
          );
          const rsa_signature_async = await Cryptopp.async.RSA.sign(
            rsa_encrypted_async,
            rsa_keypair.private,
            'PKCS1v15_SHA1'
          );
          const rsa_verify_async = await Cryptopp.async.RSA.verify(
            rsa_encrypted_async,
            rsa_keypair.public,
            'PKCS1v15_SHA1',
            rsa_signature_async
          );
        set_decrypt_async(rsa_decrypted_async as string)
        set_verify_async(rsa_verify_async ? "true" : "false")
      }
      async()
    },[])
    

  const rsa_encrypted = Cryptopp.RSA.encrypt(
    MESSAGE,
    rsa_keypair.public,
    'OAEP_SHA1'
  );
  const rsa_decrypted = Cryptopp.RSA.decrypt(
    rsa_encrypted,
    rsa_keypair.private,
    'OAEP_SHA1'
  );
  const rsa_signature = Cryptopp.RSA.sign(
    rsa_encrypted,
    rsa_keypair.private,
    'PKCS1v15_SHA1'
  );
  const rsa_verify = Cryptopp.RSA.verify(
    rsa_encrypted,
    rsa_keypair.public,
    'PKCS1v15_SHA1',
    rsa_signature
  );

  let rsa_decrypted_incorrect = ""
  try{
    Cryptopp.RSA.decrypt(
        rsa_encrypted,
        rsa_keypair2.private,
        'OAEP_SHA1'
      );
  } catch (e) {}


  const rsa_verify_incorrect = Cryptopp.RSA.verify(
    rsa_encrypted,
    rsa_keypair2.public,
    'PKCS1v15_SHA1',
    rsa_signature
  );

  return (
    <>
      {/* Sync */}
      <Text testID={`rsa_decrypted`}>{rsa_decrypted}</Text>
      <Text testID={`rsa_verify`}>{rsa_verify ? 'true' : 'false'}</Text>
      {/* Async */}
      <Text testID={`rsa_decrypted_async`}>{rsa_decrypted_async}</Text>
      <Text testID={`rsa_verify_async`}>{rsa_verify_async ? 'true' : 'false'}</Text>
      {/* Incorrect */}
      <Text testID={`rsa_decrypted_incorrect`}>{rsa_decrypted_incorrect}</Text>
      <Text testID={`rsa_verify_incorrect`}>
        {rsa_verify_incorrect ? 'true' : 'false'}
      </Text>
    </>
  );
};

