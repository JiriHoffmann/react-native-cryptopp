/* eslint-disable no-undef */
import { expect, device, element, by } from 'detox';

const results = {
  HMAC_generate:
    '24DA0BDE78E7E277B42188165595CCEB0DDF303B9EF93534B04C6433DD57EF78',
  HMAC_verify: 'true',
  CMAC_generate: '8C72D147FF9B25699B6898379AF44D8F',
  CMAC_verify: 'true',
};

export const messageAuthenticationTests = async () => {
  describe('Message Authentication', () => {
    beforeAll(async () => {
      await device.launchApp();
    });

    for (const val in results) {
      it(`Test ${val}`, async () => {
        await expect(element(by.id(val))).toHaveText(results[val]);
      });

      it(`Test ${val}_ab`, async () => {
        await expect(element(by.id(`${val}_ab`))).toHaveText(results[val]);
      });

      it(`Test ${val}_ab2`, async () => {
        await expect(element(by.id(`${val}_ab2`))).toHaveText(results[val]);
      });
    }
  });
};

