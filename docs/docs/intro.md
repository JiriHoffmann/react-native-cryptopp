---
sidebar_position: 0
slug: /
---

# Installation

```sh
npm install react-native-cryptopp
# or
yarn add react-native-cryptopp
```

#### iOS

```sh
cd ios && pod install
# or
npx pod install
```

Make sure [Hermes](https://reactnative.dev/docs/hermes) is enabled in your project.

As mentioned in the README, the Crypto++ library has to be compiled for all CPU architectures (4 on android, 3 on iOS) the first time it is used, then it is cached for subsequent builds.

Make sure you **DON't** run the `android build` and `pod install` at the same time! Temporary compiled files are saved inside the cryptopp folder and will overwrite each other resulting in issues when they are combined into the final library.

#### Android

You can check the following files for more information about the compilation process:

Location from the root of the project: <br/>
`node_modules/react-native-cryptopp/android/build/cryptopp_build.txt` <br/>
`node_modules/react-native-cryptopp/android/build/cryptopp_error.txt` <br/>

#### iOS

Run `pod install --verbose` instead to see compilation output.

## Optional: Using pre-compiled Crypto++ library

A drag-and-drop pre-compiled version of Crypto++ will be added to GitHub assets via GitHub Actions.
🚧 TODO 🚧

## Usage

```js
import Cryptopp from 'react-native-cryptopp';

const hash = Cryptopp.hashFunctions.SHA1('Hello World');
```
