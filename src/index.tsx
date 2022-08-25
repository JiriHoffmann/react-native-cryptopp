import { NativeModules, Platform } from 'react-native';
import { AES_BLOCK_CIPHERS, HASHES } from './constants';
import type { Cryptopp } from './types';

const cppinstall = NativeModules.Cryptopp;

if (cppinstall && typeof cppinstall.install === 'function') {
  cppinstall.install();
}

const CryptoppModuleCPP = (global as any).cryptoppModule;

if (!CryptoppModuleCPP) {
  const LINKING_ERROR =
    `The package 'react-native-cryptopp' doesn't seem to be linked. Make sure: \n\n` +
    Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
    '- You rebuilt the app after installing the package\n' +
    '- You are not using Expo managed workflow\n';
  throw new Error(LINKING_ERROR);
}

const exec = CryptoppModuleCPP.exec;
const execAsync = CryptoppModuleCPP.exec_async;
const CryptoppModule = { async: {} } as any;

// // Add aes candicates
AES_BLOCK_CIPHERS.forEach((cipherName) => {
  const encryptName = `${cipherName}_encrypt`;
  const decryptName = `${cipherName}_decrypt`;
  CryptoppModule[cipherName] = {
    encrypt: (...p: any) => exec(encryptName, ...p),
    decrypt: (...p: any) => exec(decryptName, ...p),
  };
  CryptoppModule.async[cipherName] = {
    encrypt: (...p: any) => execAsync(encryptName, ...p),
    decrypt: (...p: any) => execAsync(decryptName, ...p),
  };
});

// Add hashes
CryptoppModule.hash = {
  create: CryptoppModuleCPP.createHash, // Hash HostObject
};
CryptoppModule.async.hash = {};
HASHES.forEach((hashName) => {
  CryptoppModule.hash[hashName] = (...p: any) => exec('hash', hashName, ...p);
  CryptoppModule.async.hash[hashName] = (...p: any) =>
    execAsync('hash', hashName, ...p);
});

// // Insecure
CryptoppModule.insecure = {
  md2: (...p: any) => exec('insecure_md2', ...p),
  md4: (...p: any) => exec('insecure_md4', ...p),
  md5: (...p: any) => exec('insecure_md5', ...p),
};
CryptoppModule.async.insecure = {
  md2: (...p: any) => execAsync('insecure_md2', ...p),
  md4: (...p: any) => execAsync('insecure_md4', ...p),
  md5: (...p: any) => execAsync('insecure_md5', ...p),
};

// CMAC
CryptoppModule.CMAC = {
  generate: (...p: any) => exec('CMAC_generate', ...p),
  verify: (...p: any) => exec('CMAC_verify', ...p),
};
CryptoppModule.async.CMAC = {
  generate: (...p: any) => execAsync('CMAC_generate', ...p),
  verify: (...p: any) => execAsync('CMAC_verify', ...p),
};

// HMAC
CryptoppModule.HMAC = {
  generate: (...p: any) => exec('HMAC_generate', ...p),
  verify: (...p: any) => exec('HMAC_verify', ...p),
};
CryptoppModule.async.HMAC = {
  generate: (...p: any) => execAsync('HMAC_generate', ...p),
  verify: (...p: any) => execAsync('HMAC_verify', ...p),
};

// // Utils
CryptoppModule.utils = {
  toBase64: (...p: any) => exec('utils_toBase64', ...p),
  toBase64Url: (...p: any) => exec('utils_toBase64Url', ...p),
  toHex: (...p: any) => exec('utils_toHex', ...p),
  toUtf8: (...p: any) => exec('utils_toUtf8', ...p),
  randomBytes: (...p: any) => exec('utils_randomBytes', ...p),
  stringToBytes: (...p: any) => exec('utils_stringToBytes', ...p),
};
CryptoppModule.async.utils = {
  toBase64: (...p: any) => execAsync('utils_toBase64', ...p),
  toBase64Url: (...p: any) => execAsync('utils_toBase64Url', ...p),
  toHex: (...p: any) => execAsync('utils_toHex', ...p),
  toUtf8: (...p: any) => execAsync('utils_toUtf8', ...p),
  randomBytes: (...p: any) => execAsync('utils_randomBytes', ...p),
  stringToBytes: (...p: any) => execAsync('utils_stringToBytes', ...p),
};

// // Key Derivation
CryptoppModule.keyDerivation = {
  HKDF: (...p: any) => exec('key_derivation_HKDF', ...p),
  PKCS12_PBKDF: (...p: any) => exec('key_derivation_PKCS12_PBKDF', ...p),
  PKCS5_PBKDF1: (...p: any) => exec('key_derivation_PKCS5_PBKDF1', ...p),
  PKCS5_PBKDF2: (...p: any) => exec('key_derivation_PKCS5_PBKDF2', ...p),
  Scrypt: (...p: any) => exec('key_derivation_Scrypt', ...p),
};
CryptoppModule.async.keyDerivation = {
  HKDF: (...p: any) => execAsync('key_derivation_HKDF', ...p),
  PKCS12_PBKDF: (...p: any) => execAsync('key_derivation_PKCS12_PBKDF', ...p),
  PKCS5_PBKDF1: (...p: any) => execAsync('key_derivation_PKCS5_PBKDF1', ...p),
  PKCS5_PBKDF2: (...p: any) => execAsync('key_derivation_PKCS5_PBKDF2', ...p),
  Scrypt: (...p: any) => execAsync('key_derivation_Scrypt', ...p),
};

// // Public-key
CryptoppModule.RSA = {
  generateKeyPair: (...p: any) => exec('rsa_generateKeyPair', ...p),
  encrypt: (...p: any) => exec('rsa_encrypt', ...p),
  decrypt: (...p: any) => exec('rsa_decrypt', ...p),
  sign: (...p: any) => exec('rsa_sign', ...p),
  verify: (...p: any) => exec('rsa_verify', ...p),
  recover: (...p: any) => exec('rsa_recover', ...p),
};
CryptoppModule.async.RSA = {
  generateKeyPair: (...p: any) => execAsync('rsa_generateKeyPair', ...p),
  encrypt: (...p: any) => execAsync('rsa_encrypt', ...p),
  decrypt: (...p: any) => execAsync('rsa_decrypt', ...p),
  sign: (...p: any) => execAsync('rsa_sign', ...p),
  verify: (...p: any) => execAsync('rsa_verify', ...p),
  recover: (...p: any) => execAsync('rsa_recover', ...p),
};

export default CryptoppModule as Cryptopp;
export * from './types';
