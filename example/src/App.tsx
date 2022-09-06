/* eslint-disable react-hooks/exhaustive-deps */
import React, { useState, useEffect, useMemo } from 'react';

import {
  StyleSheet,
  SafeAreaView,
  View,
  Text,
  TextInput,
  TouchableOpacity,
  ScrollView,
} from 'react-native';
import Cryptopp, { BinaryLike } from 'react-native-cryptopp';
import ImagePicker from 'react-native-image-crop-picker';
import ReactNativeBlobUtil from 'react-native-blob-util';
import { PerformanceNow, timeDelta } from './utils';
import { useCallback } from 'react';

export default function App() {
  const [textInput, setTextInput] = useState('');
  const [result, setResult] = useState<any>({});
  const aes_key = useMemo(() => Cryptopp.utils.randomBytes(32), []);
  const aes_iv = useMemo(() => Cryptopp.utils.randomBytes(16), []);
  const rsa_keypair = useMemo(
    () => Cryptopp.RSA.generateKeyPair(2048, 65537),
    []
  );
  const rsa_keypair2 = useMemo(
    () => Cryptopp.RSA.generateKeyPair(2048, 65537),
    []
  );

  useEffect(() => {
    if (textInput.length > 0) {
      const results = _processData(textInput, aes_key, aes_iv, false);
      setResult(results);
    }
  }, [textInput, aes_key, aes_iv]);

  const _openImagePicker = useCallback(() => {
    ImagePicker.openPicker({}).then((image) => {
      ReactNativeBlobUtil.fs
        .readFile(image.path, 'base64')
        .then((data) => {
          setResult(_processData(data, aes_key, aes_iv, true));
        })
        .catch(() => {});
    });
  }, [aes_key, aes_iv]);

  const _processData = useCallback(
    (str: string, key: BinaryLike, iv: BinaryLike, isImage: boolean) => {
      const aes_start = PerformanceNow();

      // AES encrypt and decrypt
      const aes_encrypted = Cryptopp.AES.encrypt(str, key, iv, 'cbc');
      const aes_decrypted = Cryptopp.AES.decrypt(aes_encrypted, key, iv, 'cbc');
      const aes_key_hex = Cryptopp.utils.toHex(aes_key);
      const aes_time = timeDelta(aes_start, PerformanceNow());

      let rsa_encrypted = '';
      let rsa_decrypted = '';
      let rsa_signature = '';
      let rsa_verify = '';
      let rsa_time = '';

      // RSA - images are most likely larger than the rsa encryption key
      if (!isImage) {
        const rsa_start = PerformanceNow();

        rsa_encrypted = Cryptopp.RSA.encrypt(
          str,
          rsa_keypair.public,
          'OAEP_SHA1'
        );
        rsa_decrypted = Cryptopp.RSA.decrypt(
          rsa_encrypted,
          rsa_keypair.private,
          'OAEP_SHA1'
        );
        rsa_signature = Cryptopp.RSA.sign(
          rsa_encrypted,
          rsa_keypair2.private,
          'PKCS1v15_SHA1'
        );
        rsa_verify = Cryptopp.RSA.verify(
          rsa_encrypted,
          rsa_keypair2.public,
          'PKCS1v15_SHA1',
          rsa_signature
        ).toString();

        rsa_time = timeDelta(rsa_start, PerformanceNow());
      }

      const cmac_start = PerformanceNow();
      // CMAC
      const cmac = Cryptopp.CMAC.generate(str, key, 'AES', 'hex');
      const cmac_verify = Cryptopp.CMAC.verify(
        str,
        key,
        'AES',
        cmac,
        'hex'
      ).toString();
      const cmac_time = timeDelta(cmac_start, PerformanceNow());

      const hmac_start = PerformanceNow();
      // HMAC
      const hmac = Cryptopp.HMAC.generate(str, key, 'SHA256');
      const hmac_verify = Cryptopp.HMAC.verify(
        str,
        key,
        'SHA256',
        hmac
      ).toString();
      const hmac_time = timeDelta(hmac_start, PerformanceNow());

      // Hashes
      const hash = Cryptopp.hash.create('BLAKE2b');
      Array.from(str).forEach((c) => hash.update(c));
      const BLAKE2b_progressive = hash.finalize();

      const hashes_start = PerformanceNow();
      const BLAKE2b = Cryptopp.hash.BLAKE2b(str);
      const BLAKE2s = Cryptopp.hash.BLAKE2s(str);
      const Keccak_256 = Cryptopp.hash.Keccak256(str);
      const LSH_256 = Cryptopp.hash.LSH256(str);
      const sha = Cryptopp.hash.SHA1(str);
      const sha2_512 = Cryptopp.hash.SHA512(str);
      const sha3_512 = Cryptopp.hash.SHA3_512(str);
      const SHAKE_128 = Cryptopp.hash.SHAKE128(str);
      const SipHash_2_4_64 = Cryptopp.hash.SipHash_2_4_64(str);
      const SM3 = Cryptopp.hash.SM3(str);
      const Tiger = Cryptopp.hash.Tiger(str);
      const RIPEMD_128 = Cryptopp.hash.RIPEMD128(str);
      const Whirlpool = Cryptopp.hash.WHIRLPOOL(str);
      const CRC32 = Cryptopp.hash.CRC32(str);

      // Insecure hashes
      const md2 = Cryptopp.insecure.md2(str);
      const md4 = Cryptopp.insecure.md4(str);
      const md5 = Cryptopp.insecure.md5(str);
      const hashes_time = timeDelta(hashes_start, PerformanceNow());

      // Encoding manipulation
      const encoding_start = PerformanceNow();
      const base64 = Cryptopp.utils.toBase64(str);
      const base64Url = Cryptopp.utils.toBase64Url(str);
      const hexFromB64URL = Cryptopp.utils.toHex(base64Url, 'base64url');
      const hexFromUtf8 = Cryptopp.utils.toHex(str);
      const encoding_time = timeDelta(encoding_start, PerformanceNow());

      // Key padding
      const key_padding_start = PerformanceNow();
      const PKCS12_PBKDF = Cryptopp.keyDerivation.PKCS12_PBKDF(
        str,
        'salt',
        'SHA256',
        1024
      );
      const PKCS5_PBKDF1 = Cryptopp.keyDerivation.PKCS5_PBKDF1(
        str,
        'salt',
        'SHA256',
        1024
      );
      const PKCS5_PBKDF2 = Cryptopp.keyDerivation.PKCS5_PBKDF2(
        str,
        'salt',
        'SHA256',
        1024
      );
      const HKDF = Cryptopp.keyDerivation.HKDF(
        str,
        'salt',
        'HKDF key derivation',
        'SHA1'
      );
      const Scrypt = Cryptopp.keyDerivation.Scrypt(
        str,
        'NaCl',
        1024,
        8,
        16,
        16
      );
      const key_padding_time = timeDelta(key_padding_start, PerformanceNow());

      if (isImage)
        return {
          aes_time,
          hashes_time,
          encoding_time,
          key_padding_time,
        };

      return {
        aes_encrypted,
        aes_decrypted,
        aes_key_hex,
        aes_time,
        rsa_encrypted,
        rsa_decrypted,
        rsa_signature,
        rsa_verify,
        rsa_time,
        hmac,
        hmac_verify,
        hmac_time,
        cmac,
        cmac_verify,
        cmac_time,
        BLAKE2b_progressive,
        BLAKE2b,
        BLAKE2s,
        Keccak_256,
        LSH_256,
        sha,
        sha2_512,
        sha3_512,
        SHAKE_128,
        SipHash_2_4_64,
        SM3,
        Tiger,
        RIPEMD_128,
        Whirlpool,
        CRC32,
        md2,
        md4,
        md5,
        hashes_time,
        base64,
        base64Url,
        hexFromB64URL,
        hexFromUtf8,
        encoding_time,
        PKCS12_PBKDF,
        PKCS5_PBKDF1,
        PKCS5_PBKDF2,
        HKDF,
        Scrypt,
        key_padding_time,
      };
    },
    []
  );

  return (
    <SafeAreaView style={styles.container}>
      <Text style={styles.header}>Input value:</Text>
      <TextInput
        value={textInput}
        onChangeText={setTextInput}
        style={styles.textInput}
      />
      <Text style={styles.noteText}>
        Note: Only text input results are diplayed since rendering is slow for
        extremely long texts. Times are measures for all operations in category,
        i.e. the RSA time taken is for encryption, decryption, signature and
        verification.
      </Text>

      <View style={styles.inputButtonsContainer}>
        <TouchableOpacity
          style={styles.button}
          onPress={() => setTextInput('')}
        >
          <Text style={styles.buttonText}>Clear</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.button} onPress={_openImagePicker}>
          <Text style={styles.buttonText}>Open image picker</Text>
        </TouchableOpacity>
      </View>
      <Text style={styles.header}>Results:</Text>
      <ScrollView
        style={styles.resultsContainer}
        contentContainerStyle={styles.resultsContentContainer}
      >
        {Object.keys(result).map((key) => (
          <Text key={key} style={styles.result} numberOfLines={1}>
            {/* @ts-ignore */}
            {key}: {`|${result[key]}|`}
          </Text>
        ))}
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginHorizontal: '5%',
    marginVertical: 10,
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
  header: {
    fontSize: 20,
  },
  textInput: {
    borderColor: 'gray',
    borderWidth: 1,
    borderRadius: 5,
    height: 40,
    padding: 10,
  },
  noteText: {
    textAlign: 'center',
    fontSize: 13,
  },
  inputButtonsContainer: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    marginVertical: 5,
  },
  button: {
    flex: 1,
    backgroundColor: '#ddd',
    borderRadius: 5,
    marginHorizontal: 5,
    height: 40,
    justifyContent: 'center',
  },
  buttonText: {
    textAlign: 'center',
    fontSize: 18,
  },
  result: {
    height: 20,
    marginVertical: 2,
  },
  resultsContainer: {
    flex: 1,
  },
  resultsContentContainer: { paddingBottom: 50 },
});
