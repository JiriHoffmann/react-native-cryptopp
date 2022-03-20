/* eslint-disable react-hooks/exhaustive-deps */
import React, { useState, useEffect, useMemo } from 'react';

import {
  StyleSheet,
  SafeAreaView,
  View,
  Text,
  TextInput,
  TouchableOpacity,
} from 'react-native';
import Cryptopp from 'react-native-cryptopp';
import ImagePicker from 'react-native-image-crop-picker';
import ReactNativeBlobUtil from 'react-native-blob-util';
import { PerformanceNow, timeDelta } from './utils';
import { useCallback } from 'react';
import type { BinaryLike } from 'src/types';
import { ScrollView } from 'react-native';

export default function App() {
  const [textInput, setTextInput] = useState('');
  const [result, setResult] = useState<any>({});
  const aes_key = useMemo(() => Cryptopp.utils.randomBytes(32), []);
  const aes_iv = useMemo(() => Cryptopp.utils.randomBytes(16), []);
  const rsa_keypair = useMemo(() => Cryptopp.RSA.generateKeyPair(2048), []);
  const rsa_keypair2 = useMemo(() => Cryptopp.RSA.generateKeyPair(2048), []);

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

        rsa_encrypted = Cryptopp.RSA.encrypt(str, rsa_keypair.public);
        rsa_decrypted = Cryptopp.RSA.decrypt(
          rsa_encrypted,
          rsa_keypair.private
        );
        rsa_signature = Cryptopp.RSA.sign(rsa_encrypted, rsa_keypair2.private);
        rsa_verify = Cryptopp.RSA.verify(
          rsa_encrypted,
          rsa_keypair2.public,
          rsa_signature
        ).toString();
        rsa_time = timeDelta(rsa_start, PerformanceNow());
      }

      // SHA hashes
      const hashes_start = PerformanceNow();
      const sha = Cryptopp.SHA.sha1(str);
      const sha2 = Cryptopp.SHA.sha2(str, '512');
      const sha3 = Cryptopp.SHA.sha3(str, '512');

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
      const pbkdf12 = Cryptopp.keyDerivation.pbkdf12(
        str,
        'salt',
        'SHA256',
        1024
      );
      const pkbdf1 = Cryptopp.keyDerivation.pkcs5_pbkdf1(
        str,
        'salt',
        'SHA256',
        1024
      );
      const pkbdf2 = Cryptopp.keyDerivation.pkcs5_pbkdf2(
        str,
        'salt',
        'SHA256',
        1024
      );
      const hkdf = Cryptopp.keyDerivation.hkdf(
        str,
        'salt',
        'HKDF key derivation',
        'SHA1'
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
        sha,
        sha2,
        sha3,
        md2,
        md4,
        md5,
        hashes_time,
        base64,
        base64Url,
        hexFromB64URL,
        hexFromUtf8,
        encoding_time,
        pbkdf12,
        pkbdf1,
        pkbdf2,
        hkdf,
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
      <Text style={styles.header}>All results:</Text>
      <ScrollView
        style={styles.resultsContainer}
        contentContainerStyle={styles.resultsContentContainer}
      >
        {Object.keys(result).map((key) => (
          <Text key={key} style={styles.result} numberOfLines={1}>
            {/* @ts-ignore */}
            {key}: {result[key]}
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
