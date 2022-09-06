---
sidebar_position: 0
slug: /
---

# Installation

Make sure [Hermes](https://reactnative.dev/docs/hermes) is enabled in your project.

```bash
npm install react-native-cryptopp
# or
yarn add react-native-cryptopp
```

As mentioned in the `README`, the Crypto++ library has to be compiled for all CPU architectures (4 on android, 3 on iOS) the first time it is used, then it is cached for subsequent builds.

Compilation can be also manually triggered by running the following command:

Note: Make sure `ANDROID_NDK_ROOT` and `ANDROID_SDK_ROOT` are set correctly.

```bash
yarn node node_modules/react-native-cryptopp/scripts/compile_cryptopp.js
```

### Optional: Using pre-compiled Crypto++ library

Pre-compiled Crypto++ libraries via GitHub Actions are available for iOS and Android. They can be downloaded manually from releases on GitHub or by running the following command:

```bash
yarn node node_modules/react-native-cryptopp/scripts/download_cryptopp.js
```

You can also add it as a `postinstall` script in your `package.json` file.

### Installation: iOS

```bash
cd ios && pod install
# or
npx pod install
# or add --verbose to see compilation output
cd ios && pod install --verbose
```

Make sure you **DON't** run the `android build` and `pod install` at the same time! Temporary compiled files are saved inside the cryptopp folder and will overwrite each other resulting in issues when they are combined into the final library.

### Installation: Android

Crypto++ will be compiled when you build the Adroid app for the first time. You can check the following files for more information about the compilation process:

Location from the root of the project: 
```
node_modules/react-native-cryptopp/android/build/cryptopp_build.txt
```
```
node_modules/react-native-cryptopp/android/build/cryptopp_error.txt
```

# Usage

```js
import Cryptopp from 'react-native-cryptopp';

const hash = Cryptopp.hash.SHA1('Hello World');
```
