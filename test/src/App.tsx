import React from 'react';
import { SafeAreaView } from 'react-native';
import { AesCandidates } from './AesCandidates';
import { HashFunctions } from './HashFunctions';
import { KeyDerivation } from './KeyDerivation';
import { MessageAuthentication } from './MessageAuthentication';

const App = () => {
  return (
    // eslint-disable-next-line react-native/no-inline-styles
    <SafeAreaView style={{ flex: 1 }}  testID={`container`}>
      <HashFunctions />
      <AesCandidates />
      <KeyDerivation />
      <MessageAuthentication />
    </SafeAreaView>
  );
};

export default App;
