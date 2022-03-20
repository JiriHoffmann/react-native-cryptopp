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

export default function App() {
  const [textInput, setTextInput] = useState('');
  const [result, setResult] = useState<any>({});
  const [textInputTime, setTextInputTime] = useState('0');
  const [imageInputTime, setImageInputTime] = useState('0');
  const aes_key = useMemo(() => Cryptopp.utils.randomBytes(32), []);
  const aes_iv = useMemo(() => Cryptopp.utils.randomBytes(16), []);

  useEffect(() => {
    if (textInput.length > 0) {
      const results = _processData(textInput, aes_key, aes_iv);
      setResult(results.data);
      setTextInputTime(results.time);
    }
  }, [textInput, aes_key, aes_iv]);

  const _openImagePicker = useCallback(() => {
    ImagePicker.openPicker({}).then((image) => {
      ReactNativeBlobUtil.fs
        .readFile(image.path, 'base64')
        .then((data) => {
          setImageInputTime(_processData(data, aes_key, aes_iv).time);
        })
        .catch(() => {});
    });
  }, [aes_key, aes_iv]);

  const _processData = useCallback(
    (str: string, key: BinaryLike, iv: BinaryLike) => {
      const start = PerformanceNow();
      // AES encrypt and decrypt
      const aes_encrypted = Cryptopp.AES.encrypt(str, key, iv, 'cbc');
      const aes_decrypted = Cryptopp.AES.decrypt(aes_encrypted, key, iv, 'cbc');
      const aes_key_hex = Cryptopp.utils.toHex(aes_key);

      const sha = Cryptopp.SHA.sha1(str);
      const sha2 = Cryptopp.SHA.sha2(str, '512');
      const sha3 = Cryptopp.SHA.sha3(str, '512');

      // Insecure hashes
      const md2 = Cryptopp.insecure.md2(str);
      const md4 = Cryptopp.insecure.md4(str);
      const md5 = Cryptopp.insecure.md5(str);

      // Encoding manipulation
      const base64 = Cryptopp.utils.toBase64(str);
      const base64Url = Cryptopp.utils.toBase64Url(str);
      const hexFromB64URL = Cryptopp.utils.toHex(base64Url, 'base64url');
      const hexFromUtf8 = Cryptopp.utils.toHex(str);

      // Key padding
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

      const end = PerformanceNow();
      return {
        data: {
          aes_encrypted,
          aes_decrypted,
          aes_key_hex,
          sha,
          sha2,
          sha3,
          md2,
          md4,
          md5,
          base64,
          base64Url,
          hexFromB64URL,
          hexFromUtf8,
          pbkdf12,
          pkbdf1,
          pkbdf2,
          hkdf,
        },
        time: timeDelta(start, end),
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
        extremely long texts.
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

      <View style={styles.inputButtonsContainer}>
        <Text style={styles.timeText}>Input time: {textInputTime}ms</Text>
        <Text style={styles.timeText}>Image time: {imageInputTime}ms</Text>
      </View>

      <Text style={styles.header}>All results:</Text>
      {Object.keys(result).map((key) => (
        <Text key={key} style={styles.result} numberOfLines={1}>
          {/* @ts-ignore */}
          {key}: {result[key]}
        </Text>
      ))}
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginHorizontal: '5%',
    marginVertical: 20,
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
    height: 50,
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
    height: 50,
    justifyContent: 'center',
  },
  timeText: {
    textAlign: 'center',
    fontSize: 15,
    flex: 1,
  },
  buttonText: {
    textAlign: 'center',
    fontSize: 18,
  },
  result: {
    height: 20,
    marginVertical: 2,
  },
});
