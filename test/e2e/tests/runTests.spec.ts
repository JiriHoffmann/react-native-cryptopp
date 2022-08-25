import { expect, element, by } from 'detox';
import { aesCandicatesTests } from './aesCandidates';
import { hashFunctionsTests } from './hashFunctions';
import { keyDerivationTests } from './keyDerivation';
import { messageAuthenticationTests } from './messageAuthentication';

describe('App', () => {
  it(`Test app start`, async () => {
    await expect(element(by.id('container'))).toBeVisible();
  });
});

hashFunctionsTests();
aesCandicatesTests();
keyDerivationTests();
messageAuthenticationTests();