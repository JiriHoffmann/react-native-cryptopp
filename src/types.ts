type StandartsSHA = '224' | '256' | '384' | '512';

export interface Cryptopp {
  SHA: {
    sha1: (data: string) => string;
    sha2: (data: string, hashSize: StandartsSHA) => string;
    sha3: (data: string, hashSize: StandartsSHA) => string;
  };
}
