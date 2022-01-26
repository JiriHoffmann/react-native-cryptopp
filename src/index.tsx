import { NativeModules, Platform } from 'react-native';

const cppinstall = NativeModules.Cryptopp

if (cppinstall && typeof cppinstall.install === 'function') {
  cppinstall.install()
} else {
  const LINKING_ERROR =
  `The package 'react-native-cryptopp' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';
  throw new Error(LINKING_ERROR);
}

const Cryptopp = (global as any).cryptoppModule


export { Cryptopp }