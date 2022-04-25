import {expect, device, element, by} from 'detox';

describe('Example', () => {
  beforeEach(async () => {
    await device.launchApp();
  });

  it('should show "Step One"', async () => {
    await expect(element(by.text('Step One'))).toBeVisible();
  });

  it('should show "See Your Changes"', async () => {
    await expect(element(by.text('See Your Changes'))).toBeVisible();
  });
});
