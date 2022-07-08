export type CryptoppHashes =
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

export type HashObjectHashes = CryptoppHashes | 'CRC32';

export type AESBlockCiphers =
  | 'AES'
  | 'RC6'
  | 'MARS'
  | 'Twofish'
  | 'Serpent'
  | 'CAST256';

export type BlockCiphers =
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

export type AES_and_Candidates = {
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
};
