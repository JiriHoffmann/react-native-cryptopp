type SHA_Standarts = '224' | '256' | '384' | '512';
type AES_Modes = 'ecb' | 'cbc' | 'cfb' | 'ofb' | 'ctr';

export interface Cryptopp {
  SHA: {
    sha1: (data: string) => string;
    sha2: (data: string, hashSize: SHA_Standarts) => string;
    sha3: (data: string, hashSize: SHA_Standarts) => string;
  };
  AES: {
    encrypt: (data: string, key: string, iv: string, mode: AES_Modes) => string;
    decrypt: (data: string, key: string, iv: string, mode: AES_Modes) => string;
  };
  utilsJS: {
    stringToArrayBuffer: (str: string) => ArrayBuffer;
    arrayBufferToString: (buf: ArrayBuffer) => string;
  };
}
