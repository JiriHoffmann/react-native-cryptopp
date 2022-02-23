import * as React from 'react';

import {
  StyleSheet,
  View,
  Text,
  Button,
  TextInput,
  TouchableOpacity,
} from 'react-native';
import Cryptopp from 'react-native-cryptopp';
import ImagePicker from 'react-native-image-crop-picker';
import ReactNativeBlobUtil from 'react-native-blob-util';
import { useEffect } from 'react';
import { useState } from 'react';

export default function App() {
  const [textInput, setTextInput] = useState('');
  const [result, setResult] = useState({
    aes: '',
    sha: '',
    sha2: '',
    sha3: '',
  });

  useEffect(() => {
    const key = '12345678901234561234567890123456';
    const iv = '12345678901234561234567890123456';

    const aes = Cryptopp.AES.encrypt(textInput, key, iv, 'cbc');
    const sha = Cryptopp.SHA.sha1(textInput);
    const sha2 = Cryptopp.SHA.sha2(textInput, '512');
    const sha3 = Cryptopp.SHA.sha3(textInput, '512');

    setResult({
      aes,
      sha,
      sha2,
      sha3,
    });
  }, [textInput]);

  const _openImagePicker = () => {
    ImagePicker.openPicker({
      width: 300,
      height: 400,
      cropping: true,
    }).then((image) => {
      ReactNativeBlobUtil.fs.readFile(image.path, 'base64').then((data) => {
        setTextInput(data);
      });
    });
  };

  return (
    <View style={styles.container}>
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
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginHorizontal: '5%',
    marginVertical: 20,
    // alignItems: 'center',
    // justifyContent: 'center',
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
