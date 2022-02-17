import * as React from 'react';

import { StyleSheet, View, Text } from 'react-native';
import Cryptopp from 'react-native-cryptopp';

export default function App() {
  const [result, setResult] = React.useState<string>();

  React.useEffect(() => {
    setResult(Cryptopp.SHA.sha1('Hello World'));
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {result}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
