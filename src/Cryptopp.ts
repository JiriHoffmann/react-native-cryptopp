import type { Hash } from './HostObjects';
import type {
  AESBlockCiphers,
  AES_and_Candidates,
  BinaryLike,
  BinaryLikeEncodingInput,
  BinaryLikeEncodingOutput,
  BitSize,
  BlockCiphers,
  CryptoppHashes,
  HashObjectHashes,
  KeyDerivationHash,
  RIPEMD_Size,
  RSA_EncryptionScheme,
  RSA_PSS,
  RSA_PSSR,
  RSA_SignatureScheme,
  RSA_SSA,
  SHAKE_Size,
  SipHash_Type,
} from './types';

export interface Cryptopp {
  // AES and AES candidates
  AES: AES_and_Candidates;
  RC6: AES_and_Candidates;
  MARS: AES_and_Candidates;
  Twofish: AES_and_Candidates;
  Serpent: AES_and_Candidates;
  CAST256: AES_and_Candidates;

  // Message authentication codes
  CMAC: {
    generate: <T extends BinaryLike>(
      data: T,
      key: BinaryLike,
      cipher: AESBlockCiphers | BlockCiphers,
      encodeTo?: BinaryLikeEncodingOutput
    ) => T;
    verify: (
      data: BinaryLike,
      key: BinaryLike,
      cipher: AESBlockCiphers | BlockCiphers,
      mac: BinaryLike,
      macStringEncoding?: BinaryLikeEncodingInput
    ) => boolean;
  };
  HMAC: {
    generate: <T extends BinaryLike>(
      data: T,
      key: BinaryLike,
      hash: CryptoppHashes,
      encodeTo?: BinaryLikeEncodingOutput
    ) => T;
    verify: (
      data: BinaryLike,
      key: BinaryLike,
      hash: CryptoppHashes,
      mac: BinaryLike,
      macStringEncoding?: BinaryLikeEncodingInput
    ) => boolean;
  };

  // Hash functions
  hash: {
    create: (hashType: HashObjectHashes) => Hash;
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
  };
  keyDerivation: {
    pbkdf12: <T extends BinaryLike>(
      password: BinaryLike,
      salt: BinaryLike,
      hash: KeyDerivationHash,
      iterations: number
    ) => T;
    pkcs5_pbkdf1: <T extends BinaryLike>(
      password: BinaryLike,
      salt: BinaryLike,
      hash: KeyDerivationHash,
      iterations: number
    ) => T;
    pkcs5_pbkdf2: <T extends BinaryLike>(
      password: BinaryLike,
      salf: BinaryLike,
      hash: KeyDerivationHash,
      iterations: number
    ) => T;
    hkdf: <T extends BinaryLike>(
      password: BinaryLike,
      salt: BinaryLike,
      hash: KeyDerivationHash,
      info: BinaryLike
    ) => T;
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
      stringEncoding?: BinaryLikeEncodingInput
    ) => string;
    toBase64Url: (
      input: BinaryLike,
      stringEncoding?: BinaryLikeEncodingInput
    ) => string;
    toHex: (
      data: BinaryLike,
      stringEncoding?: BinaryLikeEncodingInput
    ) => string;
    toUtf8: (
      input: BinaryLike,
      stringEncoding?: BinaryLikeEncodingInput
    ) => string;
  };
}
