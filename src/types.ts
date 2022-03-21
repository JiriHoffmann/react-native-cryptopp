export type BitSize = '224' | '256' | '384' | '512';
export type SipHash_Type = '2_4_64' | '4_8_128';
export type SHAKE_Size = '128' | '256';
export type RIPEMD_Size = '128' | '160' | '256' | '320';
export type AES_Modes = 'ecb' | 'cbc' | 'cfb' | 'ofb' | 'ctr';
export type BinaryLike = string | ArrayBuffer;
export type BinaryLikeEncoding = 'utf8' | 'hex' | 'base64' | 'base64url';
export type KeyDerivationHash =
  | 'SHA1'
  | 'SHA256'
  | 'SHA512'
  | 'SHA3_256'
  | 'SHA3_512'
  | 'SHAKE128'
  | 'SHAKE256'
  | 'BLAKE2b'
  | 'BLAKE2s'
  | 'LSH256'
  | 'LSH512'
  | 'SM3';

export interface Cryptopp {
  hashFunctions: {
    BLAKE2b: (data: BinaryLike) => string;
    BLAKE2s: (data: BinaryLike) => string;
    Keccak: (data: BinaryLike, size: BitSize) => string;
    LSH: (data: BinaryLike, size: BitSize) => string;
    SHA1: (data: string) => string;
    SHA2: (data: string, size: BitSize) => string;
    SHA3: (data: string, size: BitSize) => string;
    SHAKE: (data: string, size: SHAKE_Size) => string;
    SipHash: (data: string, type: SipHash_Type) => string;
    SM3: (data: string) => string;
    Tiger: (data: string) => string;
    RIPEMD: (data: string, size: RIPEMD_Size) => string;
    WHIRLPOOL: (data: string) => string;
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
  RSA: {
    generateKeyPair: (keySize: number) => {
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
    encrypt: (data: BinaryLike, publicKey: string) => string;
    decrypt: (data: BinaryLike, privateKey: string) => string;
    sign: (data: BinaryLike, privateKey: string) => string;
    verify: (data: BinaryLike, publicKey: string, signature: string) => boolean;
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
