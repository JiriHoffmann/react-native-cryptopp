export type SHA_Standarts = '224' | '256' | '384' | '512';
export type AES_Modes = 'ecb' | 'cbc' | 'cfb' | 'ofb' | 'ctr';
export type BinaryLike = string | ArrayBuffer;
export type BinaryLikeEncoding = 'utf8' | 'hex' | 'base64' | 'base64url';
export type KeyDerivationHash =
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
      data: BinaryLike,
      key: BinaryLike,
      iv: BinaryLike,
      mode: AES_Modes,
      encodeTo?: BinaryLikeEncoding
    ) => string;
    decrypt: (
      data: BinaryLike,
      key: BinaryLike,
      iv: BinaryLike,
      mode: AES_Modes,
      dataEncoding?: BinaryLikeEncoding
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
    // ArrayBuffer generation
    randomBytes: (size: number) => ArrayBuffer;
    stringToBytes: (
      string: string,
      stringEncoding?: BinaryLikeEncoding
    ) => ArrayBuffer;

    // Encoding manipulation
    toBase64: (data: BinaryLike, dataEncoding?: BinaryLikeEncoding) => string;
    toBase64Url: (
      data: BinaryLike,
      dataEncoding?: BinaryLikeEncoding
    ) => string;
    toHex: (data: BinaryLike, dataEncoding?: BinaryLikeEncoding) => string;
    toUtf8: (data: BinaryLike, dataEncoding?: BinaryLikeEncoding) => string;
  };
}
