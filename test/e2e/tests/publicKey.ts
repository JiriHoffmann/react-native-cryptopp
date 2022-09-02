import { expect, element, by, waitFor } from 'detox';

const MESSAGE = 'Secret message';

export const publicKeyTests = async () => {
  describe('Public key', () => {

    // RSA
    it(`Test rsa_decrypted`, async () => {
        await expect(element(by.id(`rsa_decrypted`))).toHaveText(MESSAGE);
      });

      it(`Test rsa_verify`, async () => {
        await expect(element(by.id(`rsa_verify`))).toHaveText('true');
      });

     // RSA Async
    it(`Test rsa_decrypted_async`, async () => {
      await expect(element(by.id(`rsa_decrypted_async`))).toHaveText(MESSAGE);
    });

    it(`Test rsa_verify_async`, async () => {
      await expect(element(by.id(`rsa_verify_async`))).toHaveText('true');
    });

    // RSA incorrect
    it(`Test rsa_decrypted_incorrect`, async () => {
      await waitFor(element(by.id(`rsa_decrypted_incorrect`)))
        .not.toHaveText(MESSAGE)
        .withTimeout(1000);
    });

    it(`Test rsa_verify_incorrect`, async () => {
      await waitFor(element(by.id(`rsa_verify_incorrect`)))
      .toHaveText('false')
        .withTimeout(1000);
    });
  });
};

