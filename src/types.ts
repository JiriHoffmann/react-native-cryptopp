export type BitSize = '224' | '256' | '384' | '512';
export type SipHash_Type = '2_4_64' | '4_8_128';
export type SHAKE_Size = '128' | '256';
export type RIPEMD_Size = '128' | '160' | '256' | '320';
export type AES_Modes =
  | 'ecb'
  | 'cbc'
  | 'cbc_cts'
  | 'cfb'
  | 'ofb'
  | 'ctr'
  | 'xts';
export type BinaryLike = string | ArrayBuffer;
export type BinaryLikeEncodingInput = 'utf8' | 'hex' | 'base64' | 'base64url';
export type BinaryLikeEncodingOutput = 'hex' | 'base64' | 'base64url';
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

export type RSA_EncryptionScheme = 'OAEP_SHA1' | 'OAEP_SHA256' | 'PKCS1v15';
export type RSA_SSA = 'PKCS1v15_SHA1' | 'PKCS1v15_SHA256';
export type RSA_PSSR = 'PSSR_SHA1' | 'PSSR_SHA256' | 'PSSR_Whirlpool';
export type RSA_SignatureScheme = RSA_SSA | RSA_PSSR;

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
      encodeTo?: BinaryLikeEncodingOutput
    ) => string;
    decrypt: (
      data: BinaryLike,
      key: BinaryLike,
      iv: BinaryLike,
      mode: AES_Modes,
      dataEncoding?: BinaryLikeEncodingInput
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
    encrypt: (
      data: BinaryLike,
      publicKey: string,
      encryptionScheme: RSA_EncryptionScheme
    ) => string;
    decrypt: (
      data: BinaryLike,
      privateKey: string,
      encryptionScheme: RSA_EncryptionScheme
    ) => string;
    sign: (
      data: BinaryLike,
      privateKey: string,
      signatureScheme: RSA_SignatureScheme
    ) => string;
    verify: (
      data: BinaryLike,
      publicKey: string,
      signatureScheme: RSA_SSA,
      signature: string
    ) => boolean;
    recover: (
      signature: string,
      publicKey: string,
      signatureScheme: RSA_PSSR
    ) => boolean;
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
      hash: KeyDerivationHash,
      info: BinaryLike
    ) => string;
  };
  insecure: {
    md2: (data: BinaryLike) => string;
    md4: (data: BinaryLike) => string;
    md5: (data: BinaryLike) => string;
  };

  utils: {
    // ArrayBuffer generation
    randomBytes: (size: number) => ArrayBuffer;
    stringToBytes: (
      string: string,
      stringEncoding?: BinaryLikeEncodingInput
    ) => ArrayBuffer;

    // Encoding manipulation
    toBase64: (
      input: BinaryLike,
      inputEncoding?: BinaryLikeEncodingInput
    ) => string;
    toBase64Url: (
      input: BinaryLike,
      inputEncoding?: BinaryLikeEncodingInput
    ) => string;
    toHex: (
      data: BinaryLike,
      inputEncoding?: BinaryLikeEncodingInput
    ) => string;
    toUtf8: (
      input: BinaryLike,
      inputEncoding?: BinaryLikeEncodingInput
    ) => string;
  };
}
