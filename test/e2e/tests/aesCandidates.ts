import { expect, element, by } from 'detox';

const msg = 'CBC Mode Test';

const results = {
  AES_cbc_encrypted: '8BCD1071F06813F1DEC5FB727F7451E3',
  AES_cfb_encrypted: '0AF1D5C39A2A756BE36FD5378B',
  AES_ctr_encrypted: '0AF1D5C39A2A756BE36FD5378B',
  AES_ecb_encrypted: '3AF9F5DFFE4DB5B6B4A8C46C54DE60B4',
  AES_ofb_encrypted: '0AF1D5C39A2A756BE36FD5378B',

  RC6_cbc_encrypted: 'EF2FEAEEDC5EB0310A55C0DC9C936450',
  Twofish_cbc_encrypted: 'BCD4B28F01B0CB68424FEFED3D9483BA',
};
const AES_B64 = 'i80QcfBoE/Hexftyf3RR4w==';

export const aesCandicatesTests = async () => {
  describe('AES', () => {

    // Test encryption
    for (const val in results) {
      it(`Test ${val}`, async () => {
        await expect(element(by.id(val))).toHaveText(results[val]);
      });
    }

    // ArrayBuffers
    it(`Test AES_encrypted_ab`, async () => {
      await expect(element(by.id('AES_encrypted_ab'))).toHaveText(
        results.AES_cbc_encrypted
      );
    });

    it(`Test AES_decrypted_ab`, async () => {
      await expect(element(by.id('AES_decrypted_ab'))).toHaveText(msg);
    });

    // Base64
    it(`Test AES_encrypted_b64`, async () => {
        await expect(element(by.id('AES_encrypted_b64'))).toHaveText(AES_B64);
      });

    it(`Test AES_decrypted_b64`, async () => {
      await expect(element(by.id('AES_decrypted_b64'))).toHaveText(msg);
    });
  });
};

