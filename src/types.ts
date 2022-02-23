type SHA_Standarts = '224' | '256' | '384' | '512';
type AES_Modes = 'ecb' | 'cbc' | 'cfb' | 'ofb' | 'ctr';

export interface Cryptopp {
  SHA: {
    sha1: (data: string | ArrayBuffer) => string;
    sha2: (data: string | ArrayBuffer, hashSize: SHA_Standarts) => string;
    sha3: (data: string | ArrayBuffer, hashSize: SHA_Standarts) => string;
  };
  AES: {
    encrypt: (
      data: string | ArrayBuffer,
      key: string | ArrayBuffer,
      iv: string | ArrayBuffer,
      mode: AES_Modes
    ) => string;
    decrypt: (
      data: string | ArrayBuffer,
      key: string | ArrayBuffer,
      iv: string | ArrayBuffer,
      mode: AES_Modes
    ) => string;
  };
  utils: {
    toBase64: (data: string | ArrayBuffer) => string;
    fromBase64: (data: string | ArrayBuffer) => string;
    toHex: (data: string | ArrayBuffer) => string;
    fromHex: (data: string | ArrayBuffer) => string;
  };
  utilsJS: {
    stringToArrayBuffer: (str: string) => ArrayBuffer;
    arrayBufferToString: (buf: ArrayBuffer) => string;
  };
}
