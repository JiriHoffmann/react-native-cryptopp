import React from 'react';
import { SafeAreaView } from 'react-native';

import { HashFunctions } from './HashFunctions';

const App = () => {
  return (
    // eslint-disable-next-line react-native/no-inline-styles
    <SafeAreaView style={{ flex: 1 }}>
      <HashFunctions />
    </SafeAreaView>
  );
};

export default App;
