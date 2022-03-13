type SHA_Standarts = '224' | '256' | '384' | '512';
type AES_Modes = 'ecb' | 'cbc' | 'cfb' | 'ofb' | 'ctr';
type BinaryLike = string | ArrayBuffer;
type KeyDerivationHash =
  | 'SHA1'
  | 'SHA256'
  | 'SHA512'
  | 'SHA3_256'
  | 'SHA3_512'
  | 'BLAKE2b'
  | 'BLAKE2s';

export interface Cryptopp {
  SHA: {
    sha1: (data: string) => string;
    sha2: (data: string, hashSize: SHA_Standarts) => string;
    sha3: (data: string, hashSize: SHA_Standarts) => string;
  };
  AES: {
    encrypt: (
      data: string,
      key: BinaryLike,
      iv: BinaryLike,
      mode: AES_Modes
    ) => string;
    decrypt: (
      data: string,
      key: BinaryLike,
      iv: BinaryLike,
      mode: AES_Modes
    ) => string;
  };
  keyDerivation: {
    pbkdf12: (
      password: BinaryLike,
      salt: BinaryLike,
      hash: KeyDerivationHash,
      iterations: number
    ) => string;
    pkcs5_pbkdf1: (
      password: BinaryLike,
      salt: BinaryLike,
      hash: KeyDerivationHash,
      iterations: number
    ) => string;
    pkcs5_pbkdf2: (
      password: BinaryLike,
      salf: BinaryLike,
      hash: KeyDerivationHash,
      iterations: number
    ) => string;
    hkdf: (
      password: BinaryLike,
      salt: BinaryLike,
      info: BinaryLike,
      hash: KeyDerivationHash
    ) => string;
  };
  insecure: {
    md2: (data: string) => string;
    md4: (data: string) => string;
    md5: (data: string) => string;
  };
  utils: {
    randomBytes: (length: number) => Buffer;
    hexToBase64: (data: BinaryLike) => string;
    base64ToHex: (data: BinaryLike) => string;
    hexToBase64Url: (data: BinaryLike) => string;
    base64UrlToHex: (data: BinaryLike) => string;
    utf8ToBase64: (data: BinaryLike) => string;
    base64ToUtf8: (data: BinaryLike) => string;
    utf8ToBase64Url: (data: BinaryLike) => string;
    base64UrlToUtf8: (data: BinaryLike) => string;
    utf8ToHex: (data: BinaryLike) => string;
    hexToUtf8: (data: BinaryLike) => string;
  };
  utilsJS: {
    stringToArrayBuffer: (str: string) => ArrayBuffer;
    arrayBufferToString: (buf: ArrayBuffer) => string;
  };
}
