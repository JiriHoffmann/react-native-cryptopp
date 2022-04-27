/* eslint-disable no-undef */
import { expect, device, element, by } from 'detox';

// Input: 'Yoda said, Do or do not. There is no try.'
const hashes: { [key: string]: string } = {
  BLAKE2b:
    '0C44A7590ADEFDE342BF065BCE28A7D714CC23C7E78D4DE3885745801BE2288184F4A1178AADA39FE698FA70CE5AA1A8BCDD2C1C454FA625C51158FBA5C70538',
  BLAKE2s: '5D847D366529D94FC535A3744B5C98EA5665CB3E714BBF0E5D03606F2CB1E203',
  Keccak_224: '63F01BF626BB936A08A000027904FA117DCE74A0FDFBC0480ACC5C88',
  Keccak_256:
    'E0C391FCAE9F92821EF33CA232A023BA0C4932A909212D767739AEA2608CF56E',
  Keccak_384:
    '0F87E65FA02DC72C707D67632FB3E1ABF7DA1E5F96AAC12EF4A10116026B96E6E30098D5D279A92B9B8B7E5F28CD2D94',
  Keccak_512:
    '7E679E1674D4CB599504809E5BA0FD36CCDDF3368EBE1E2898489DEA398267AC19D7A8B61FD4BBF8BF0A394100CC963B3711AACF776B1DC602B2FFFBBA207741',
  SHA1: '05C0042DF9A7793B7BDE3AB9724C08CF37398652',
  SHA224: '3B92A0F4CF662C9DC66AF6A4227CBE8F1E33EA2AC76F3AFB3F2C2FCB',
  SHA256: 'F00E3F70A268FBA990296B32FF2B6CE7A0757F31EC3059B13D3DB1E60D9E885C',
  SHA384:
    'D9519A9B22F753A3FF09A4CFD367474E3F038193F21806D5FF6DC86F0D559D3F3469B5C4C035F408C15AAB01A26D056B',
  SHA512:
    '51693F901D5318B542E4D788AD38611BF374CBCD0FDEB4A913167A29AF89D4530EA9848ADBF4C671B720C64882EBB9A3347CFF74657BF8FF07F07C9CD93E57D3',
  SHA3_224: '4AFDEAC719C02B95157B4240E79FA9C6602150D36186EFAE19EC9FC3',
  SHA3_256: '18CEA61486D217DCDC19246FA28BBD32660CEC3771442B5C2AB93271D32B2797',
  SHA3_384:
    'C01C93A812B2F087D9DBFEB2587B5ED0F6F68F03D1C3AC5966A8D9B9473496182A457932C92B8FA9608BD66DD705186E',
  SHA3_512:
    '3CF176B4B2387EB36CBC2B0675411FF0FFB2ED1300F63A80E7E950ADD13FD5F6F649391742AB0A6E3609001F2698A094CD4CD108B8D210E5E9CCA1542E955D43',
  SHAKE128: '96E753C4F374730DE6A18E9725D25FCE4297EEE571F1A659E118DF33EAE506C6',
  SHAKE256:
    'A53855217C4A97EDC7CD0B9D326486C0162803EF200817D9BB107E74941D8393085CD63264BBF568166EDB2CDCAA46DA9D2CAED4BD8B4F7A1CF5289C23D7918D',
  SM3: '04E8407F6642CF1594F932391B94C4C4D59255BF8F19F5969A5E98755F93129D',
  Tiger: '5E3BAC91E6793C3780529CA40A0CC478EDDC8F00F915EE70',
  RIPEMD128: 'DFD76A0D625D60CF9532FEDF67DE24A3',
  RIPEMD160: '03AC6FA16B984F54D6AE36988D9E90911A695F4A',
  RIPEMD256: 'DF29F660203349895C890E5D1DFFBB92DC211E8C35A8CA698324106D3EB9D0FC',
  RIPEMD320:
    '942E86F54F7AC3143BFE03CCEB40CB1D4E5779C17B37BCA69C7F7ECDDE1A5802905C8D477A6FB3BB',
};

// Input: 'Yoda said, Do or do not. There is no try.'
// Expected results based on: https://en.wikipedia.org/wiki/LSH_(hash_function)
const lshHashes = {
  LSH224: 'F7C53BA4034E708E74FBA42E55997CA5126BB7623688F85342F73732',
  LSH256: '5FBF365DAEA5446A7053C52B57404D77A07A5F48A1F7C1963A0898BA1B714741',
  LSH384:
    '5F344EFAA0E43CCD2E5E194D6039794B4FB431F10FB4B65FD45E9DA4ECDE0F27B66E8DBDFA47252E0D0B741BFD91F9FE',
  LSH512:
    'A3D93CFE60DC1AACDD3BD4BEF0A6985381A396C7D49D9FD177795697C3535208B5C57224BEF21084D42083E95A4BD8EB33E869812B65031C428819A1E7CE596D',
};

export const hashFunctionsTests = async () => {
  describe('HashFunctions', () => {
    beforeAll(async () => {
      await device.launchApp();
    });

    for (const val in hashes) {
      it(`Test ${val}`, async () => {
        await expect(element(by.id(val))).toHaveText(hashes[val]);
      });
    }

    for (const val in lshHashes) {
      it(`Test ${val}`, async () => {
        await expect(element(by.id(val))).toHaveText(lshHashes[val]);
      });
    }
  });
};
