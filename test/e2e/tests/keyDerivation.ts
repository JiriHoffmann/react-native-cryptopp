/* eslint-disable no-undef */
import { expect, device, element, by } from 'detox';

const results = {
  HKDF: '4FF891CB129EC9F2B4CF715897B3FC5A0F58C61EC2CD59D71C635C75810EC04763E8C36BAC7462D58820734B8B09A4FCB956743CDD6FA6976B26B1A1C00E0786',
  PKCS12_PBKDF:
    '46FB1E99AA495B548F67302782AFEF4711497437F084C66CB21B37AEB8206EF1',
  PKCS5_PBKDF1:
    'E2AF0AABF7C9B53D815876AEEE578F56F43DB6EAB44DFD207E83566C99F58BDD',
  PKCS5_PBKDF2:
    '231AFB7DCD2E860CFD58AB13372BD12C923076C3598A121960320F6FEC8A5698',
  Scrypt: 'FDBABE1C9D3472007856E7190D01E9FE',
};

export const keyDerivationTests = async () => {
  describe('Key Derivation', () => {
    beforeAll(async () => {
      await device.launchApp();
    });

    for (const val in results) {
      it(`Test ${val}`, async () => {
        await expect(element(by.id(val))).toHaveText(results[val]);
      });
    }
  });
};

