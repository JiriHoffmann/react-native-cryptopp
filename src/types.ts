import type { AES_BLOCK_CIPHERS, BLOCK_CIPHERS, HASHES } from './constants';
import type { Hash } from './HostObjects';

type PromisifyFunction<T extends (...args: any) => any> = T extends (
  ...args: infer A
) => infer R
  ? (...args: A) => Promise<R>
  : any;

export type Promisify<T> = {
  [P in keyof T]: T[P] extends (...args: any) => any
    ? PromisifyFunction<T[P]>
    : any;
};

export type HashName = typeof HASHES[number];

export type HashFunctions = {
  [p in HashName]: (data: BinaryLike) => string;
};

export type CipherAndDerivationHashName = Exclude<
  HashName,
  'SipHash_2_4_64' | 'SipHash_4_8_128'
>;

export type AESBlockCipherName = typeof AES_BLOCK_CIPHERS[number];

export type AES_Modes =
  | 'ecb'
  | 'cbc'
  | 'cbc_cts'
  | 'cfb'
  | 'ofb'
  | 'ctr'
  | 'xts';

export type BlockCiphers = typeof BLOCK_CIPHERS[number];

export type BinaryLike = string | ArrayBuffer;
export type BinaryLikeEncodingInput = 'utf8' | 'hex' | 'base64' | 'base64url';
export type BinaryLikeEncodingOutput = 'hex' | 'base64' | 'base64url';
export type KeyDerivationHashName = CipherAndDerivationHashName;

export type RSA_EncryptionScheme = 'OAEP_SHA1' | 'OAEP_SHA256' | 'PKCS1v15';
export type RSA_SSA = 'PKCS1v15_SHA1' | 'PKCS1v15_SHA256';
export type RSA_PSS = 'PSS_SHA1' | 'PSS_SHA256' | 'PSS_Whirlpool';
export type RSA_PSSR = 'PSSR_SHA1' | 'PSSR_SHA256' | 'PSSR_Whirlpool';
export type RSA_SignatureScheme = RSA_SSA | RSA_PSS | RSA_PSSR;

declare interface AES_and_Candidates {
  encrypt: <T extends BinaryLike>(
    data: T,
    key: BinaryLike,
    iv: BinaryLike,
    mode: AES_Modes,
    encodeTo?: BinaryLikeEncodingOutput
  ) => T;
  decrypt: <T extends BinaryLike>(
    data: T,
    key: BinaryLike,
    iv: BinaryLike,
    mode: AES_Modes,
    dataStringEncoding?: BinaryLikeEncodingInput
  ) => T;
}

declare interface CMAC {
  generate: <T extends BinaryLike>(
    data: T,
    key: BinaryLike,
    cipher: AESBlockCipherName | BlockCiphers,
    encodeTo?: BinaryLikeEncodingOutput
  ) => T;
  verify: (
    data: BinaryLike,
    key: BinaryLike,
    cipher: AESBlockCipherName | BlockCiphers,
    mac: BinaryLike,
    macStringEncoding?: BinaryLikeEncodingInput
  ) => boolean;
}

declare interface HMAC {
  generate: <T extends BinaryLike>(
    data: T,
    key: BinaryLike,
    hash: CipherAndDerivationHashName,
    encodeTo?: BinaryLikeEncodingOutput
  ) => T;
  verify: (
    data: BinaryLike,
    key: BinaryLike,
    hash: CipherAndDerivationHashName,
    mac: BinaryLike,
    macStringEncoding?: BinaryLikeEncodingInput
  ) => boolean;
}

declare interface RSA {
  generateKeyPair: (
    keySize: number,
    publicKeyExponent: number
  ) => {
    public: string;
    private: string;
    params: {
      n: string;
      p: string;
      q: string;
      d: string;
      e: string;
    };
  };
  encrypt: <T extends BinaryLike>(
    data: BinaryLike,
    publicKey: string,
    encryptionScheme: RSA_EncryptionScheme
  ) => T;
  decrypt: <T extends BinaryLike>(
    data: T,
    privateKey: string,
    encryptionScheme: RSA_EncryptionScheme
  ) => T;
  sign: <T extends BinaryLike>(
    data: T,
    privateKey: string,
    signatureScheme: RSA_SignatureScheme
  ) => string;
  verify: (
    data: BinaryLike,
    publicKey: string,
    signatureScheme: RSA_SSA | RSA_PSS,
    signature: string
  ) => boolean;
  recover: <T extends BinaryLike>(
    signature: T,
    publicKey: string,
    signatureScheme: RSA_PSSR
  ) => T;
}

declare interface KeyDerivation {
  pbkdf12: <T extends BinaryLike>(
    password: T,
    salt: BinaryLike,
    hash: CipherAndDerivationHashName,
    iterations: number
  ) => T;
  pkcs5_pbkdf1: <T extends BinaryLike>(
    password: T,
    salt: BinaryLike,
    hash: CipherAndDerivationHashName,
    iterations: number
  ) => T;
  pkcs5_pbkdf2: <T extends BinaryLike>(
    password: T,
    salf: BinaryLike,
    hash: CipherAndDerivationHashName,
    iterations: number
  ) => T;
  hkdf: <T extends BinaryLike>(
    password: T,
    salt: BinaryLike,
    info: BinaryLike,
    hash: CipherAndDerivationHashName
  ) => T;
  scrypt: <T extends BinaryLike>(
    password: T,
    salt: BinaryLike,
    N: number,
    r: number,
    p: number,
    dkLen: number
  ) => T;
}

declare interface Insecure {
  md2: (data: BinaryLike) => string;
  md4: (data: BinaryLike) => string;
  md5: (data: BinaryLike) => string;
}

declare interface Utils {
  randomBytes: (size: number) => ArrayBuffer;
  stringToBytes: (
    string: string,
    stringEncoding?: BinaryLikeEncodingInput
  ) => ArrayBuffer;

  // Encoding manipulation
  toBase64: (
    input: BinaryLike,
    stringEncoding?: BinaryLikeEncodingInput
  ) => string;
  toBase64Url: (
    input: BinaryLike,
    stringEncoding?: BinaryLikeEncodingInput
  ) => string;
  toHex: (data: BinaryLike, stringEncoding?: BinaryLikeEncodingInput) => string;
  toUtf8: (
    input: BinaryLike,
    stringEncoding?: BinaryLikeEncodingInput
  ) => string;
}
export declare interface Cryptopp {
  // AES and AES candidates
  AES: AES_and_Candidates;
  RC6: AES_and_Candidates;
  MARS: AES_and_Candidates;
  Twofish: AES_and_Candidates;
  Serpent: AES_and_Candidates;
  CAST256: AES_and_Candidates;
  CMAC: CMAC;
  HMAC: HMAC;
  hash: HashFunctions & {
    create: (hashType: HashName) => Hash;
  };
  RSA: RSA;
  keyDerivation: KeyDerivation;
  insecure: Insecure;
  utils: Utils;
  // Async functionality
  async: {
    AES: Promisify<AES_and_Candidates>;
    RC6: Promisify<AES_and_Candidates>;
    MARS: Promisify<AES_and_Candidates>;
    Twofish: Promisify<AES_and_Candidates>;
    Serpent: Promisify<AES_and_Candidates>;
    CAST256: Promisify<AES_and_Candidates>;
    CMAC: Promisify<CMAC>;
    HMAC: Promisify<HMAC>;
    hash: Promisify<HashFunctions>;
    RSA: Promisify<RSA>;
    keyDerivation: Promisify<KeyDerivation>;
    insecure: Promisify<Insecure>;
    utils: Promisify<Utils>;
  };
}
