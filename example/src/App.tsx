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

export default function App() {
  const [textInput, setTextInput] = useState('');
  const [result, setResult] = useState<any>({});

  const aes_key = useMemo(() => Cryptopp.utils.randomBytes(32), []);
  const aes_iv = useMemo(() => Cryptopp.utils.randomBytes(16), []);

  useEffect(() => {
    if (textInput.length > 0) {
      const aes = Cryptopp.AES.encrypt(
        textInput,
        aes_key.buffer,
        aes_iv.buffer,
        'cbc'
      );
      const sha = Cryptopp.SHA.sha1(textInput);
      const sha2 = Cryptopp.SHA.sha2(textInput, '512');
      const sha3 = Cryptopp.SHA.sha3(textInput, '512');
      const md2 = Cryptopp.insecure.md2(textInput);
      const md4 = Cryptopp.insecure.md4(textInput);
      const md5 = Cryptopp.insecure.md5(textInput);
      const base64 = Cryptopp.utils.utf8ToBase64(textInput);
      const base64Url = Cryptopp.utils.utf8ToBase64Url(textInput);
      const hex = Cryptopp.utils.utf8ToHex(textInput);

      setResult({
        aes_key,
        aes_iv,
        aes,
        sha,
        sha2,
        sha3,
        md2,
        md4,
        md5,
        base64,
        base64Url,
        hex,
      });
    }
  }, [textInput, aes_key, aes_iv]);

  const _openImagePicker = () => {
    ImagePicker.openPicker({
      width: 300,
      height: 400,
      cropping: true,
    }).then((image) => {
      ReactNativeBlobUtil.fs
        .readFile(image.path, 'base64')
        .then((data) => {
          setTextInput(data);
        })
        .catch(() => {});
    });
  };

  return (
    <SafeAreaView style={styles.container}>
      <Text style={styles.header}>Input value:</Text>
      <TextInput
        value={textInput}
        onChangeText={setTextInput}
        style={styles.textInput}
      />

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

      <Text style={styles.header}>Result:</Text>
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
  buttonText: {
    textAlign: 'center',
    fontSize: 18,
  },
  result: {
    height: 20,
    marginVertical: 2,
  },
});
