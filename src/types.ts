type CryptoppHashes =
  | 'BLAKE2b'
  | 'BLAKE2s'
  | 'Keccak_224'
  | 'Keccak_256'
  | 'Keccak_384'
  | 'Keccak_512'
  | 'LSH224'
  | 'LSH256'
  | 'LSH384'
  | 'LSH512'
  | 'SHA1'
  | 'SHA224'
  | 'SHA256'
  | 'SHA384'
  | 'SHA512'
  | 'SHA3_224'
  | 'SHA3_256'
  | 'SHA3_384'
  | 'SHA3_512'
  | 'SHAKE128'
  | 'SHAKE256'
  | 'SM3'
  | 'Tiger'
  | 'RIPEMD128'
  | 'RIPEMD160'
  | 'RIPEMD256'
  | 'RIPEMD320';

type AESBlockCiphers =
  | 'AES'
  | 'RC6'
  | 'MARS'
  | 'Twofish'
  | 'Serpent'
  | 'CAST256';

type BlockCiphers =
  | 'ARIA'
  | 'Blowfish'
  | 'Camellia'
  | 'CHAM64'
  | 'CHAM128'
  | 'HIGHT'
  | 'IDEA'
  | 'Kalyna128'
  | 'Kalyna256'
  | 'Kalyna512'
  | 'LEA'
  | 'SEED'
  | 'RC5'
  | 'SHACAL2'
  | 'SIMECK32'
  | 'SIMECK64'
  | 'SIMON64'
  | 'SIMON128'
  | 'SKIPJACK'
  | 'SPECK64'
  | 'SPECK128'
  | 'SM4'
  | 'Threefish256'
  | 'Threefish512'
  | 'Threefish1024'
  | 'DES_EDE2'
  | 'DES_EDE3'
  | 'TEA'
  | 'XTEA';

type AES_and_Candidates = {
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
export type KeyDerivationHash = CryptoppHashes;

export type RSA_EncryptionScheme = 'OAEP_SHA1' | 'OAEP_SHA256' | 'PKCS1v15';
export type RSA_SSA = 'PKCS1v15_SHA1' | 'PKCS1v15_SHA256';
export type RSA_PSSR = 'PSSR_SHA1' | 'PSSR_SHA256' | 'PSSR_Whirlpool';
export type RSA_SignatureScheme = RSA_SSA | RSA_PSSR;

export type Cryptopp = {
  // AES and AES candidates
  AES: AES_and_Candidates;
  RC6: AES_and_Candidates;
  MARS: AES_and_Candidates;
  Twofish: AES_and_Candidates;
  Serpent: AES_and_Candidates;
  CAST256: AES_and_Candidates;

  // Message authentication codes
  CMAC: {
    generate: (
      data: BinaryLike,
      key: BinaryLike,
      cipher: AESBlockCiphers | BlockCiphers,
      encodeTo?: BinaryLikeEncodingOutput
    ) => string;
    verify: (
      data: BinaryLike,
      key: BinaryLike,
      cipher: AESBlockCiphers | BlockCiphers,
      mac: BinaryLike,
      macEncoding?: BinaryLikeEncodingInput
    ) => boolean;
  };
  HMAC: {
    generate: (
      data: BinaryLike,
      key: BinaryLike,
      hash: CryptoppHashes,
      encodeTo?: BinaryLikeEncodingOutput
    ) => string;
    verify: (
      data: BinaryLike,
      key: BinaryLike,
      hash: CryptoppHashes,
      mac: BinaryLike,
      macEncoding?: BinaryLikeEncodingInput
    ) => boolean;
  };

  // Hash functions
  hashFunctions: {
    BLAKE2b: (data: BinaryLike) => string;
    BLAKE2s: (data: BinaryLike) => string;
    Keccak: (data: BinaryLike, size: BitSize) => string;
    LSH: (data: BinaryLike, size: BitSize) => string;
    SHA1: (data: BinaryLike) => string;
    SHA2: (data: BinaryLike, size: BitSize) => string;
    SHA3: (data: BinaryLike, size: BitSize) => string;
    SHAKE: (data: BinaryLike, size: SHAKE_Size) => string;
    SipHash: (data: BinaryLike, type: SipHash_Type) => string;
    SM3: (data: BinaryLike) => string;
    Tiger: (data: BinaryLike) => string;
    RIPEMD: (data: BinaryLike, size: RIPEMD_Size) => string;
    WHIRLPOOL: (data: BinaryLike) => string;
    CRC32: (data: BinaryLike) => string;
  };

  // Public-key cryptography
  RSA: {
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

  // Insecure or obsolescent algorithms retained for backwards compatibility and historical value
  insecure: {
    md2: (data: BinaryLike) => string;
    md4: (data: BinaryLike) => string;
    md5: (data: BinaryLike) => string;
  };

  // Additional utility functions
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
};
