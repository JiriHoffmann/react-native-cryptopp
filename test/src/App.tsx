import React from 'react';
import { SafeAreaView } from 'react-native';
// import { AesCandidates } from './AesCandidates';

import { HashFunctions } from './HashFunctions';

const App = () => {
  return (
    // eslint-disable-next-line react-native/no-inline-styles
    <SafeAreaView style={{ flex: 1 }}  testID={`container`}>
      <HashFunctions />
      {/* <AesCandidates /> */}
    </SafeAreaView>
  );
};

export default App;
