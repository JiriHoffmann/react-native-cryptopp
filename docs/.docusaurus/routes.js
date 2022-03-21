
import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/__docusaurus/debug',
    component: ComponentCreator('/__docusaurus/debug','3d6'),
    exact: true
  },
  {
    path: '/__docusaurus/debug/config',
    component: ComponentCreator('/__docusaurus/debug/config','914'),
    exact: true
  },
  {
    path: '/__docusaurus/debug/content',
    component: ComponentCreator('/__docusaurus/debug/content','c28'),
    exact: true
  },
  {
    path: '/__docusaurus/debug/globalData',
    component: ComponentCreator('/__docusaurus/debug/globalData','3cf'),
    exact: true
  },
  {
    path: '/__docusaurus/debug/metadata',
    component: ComponentCreator('/__docusaurus/debug/metadata','31b'),
    exact: true
  },
  {
    path: '/__docusaurus/debug/registry',
    component: ComponentCreator('/__docusaurus/debug/registry','0da'),
    exact: true
  },
  {
    path: '/__docusaurus/debug/routes',
    component: ComponentCreator('/__docusaurus/debug/routes','244'),
    exact: true
  },
  {
    path: '/blog/archive',
    component: ComponentCreator('/blog/archive','f4c'),
    exact: true
  },
  {
    path: '/',
    component: ComponentCreator('/','fb5'),
    routes: [
      {
        path: '/',
        component: ComponentCreator('/','96c'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/aes-and-aes-candidates/aes',
        component: ComponentCreator('/aes-and-aes-candidates/aes','381'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/blake2',
        component: ComponentCreator('/hash-functions/blake2','746'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/keccak',
        component: ComponentCreator('/hash-functions/keccak','d07'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/lsh',
        component: ComponentCreator('/hash-functions/lsh','ba8'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/ripemd',
        component: ComponentCreator('/hash-functions/ripemd','555'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/sha',
        component: ComponentCreator('/hash-functions/sha','996'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/shake',
        component: ComponentCreator('/hash-functions/shake','2ab'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/siphash',
        component: ComponentCreator('/hash-functions/siphash','f43'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/sm3',
        component: ComponentCreator('/hash-functions/sm3','0d3'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/tiger',
        component: ComponentCreator('/hash-functions/tiger','a31'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/hash-functions/whirlpool',
        component: ComponentCreator('/hash-functions/whirlpool','fbd'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/insecure/message-digest',
        component: ComponentCreator('/insecure/message-digest','79c'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/padding-schemes/hkdf',
        component: ComponentCreator('/padding-schemes/hkdf','0ac'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/padding-schemes/pbkdf12',
        component: ComponentCreator('/padding-schemes/pbkdf12','e9c'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/padding-schemes/pkcs5_pbkdf1',
        component: ComponentCreator('/padding-schemes/pkcs5_pbkdf1','8d7'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/padding-schemes/pkcs5_pbkdf2',
        component: ComponentCreator('/padding-schemes/pkcs5_pbkdf2','fd5'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/public-key-cryptography/rsa',
        component: ComponentCreator('/public-key-cryptography/rsa','095'),
        exact: true,
        'sidebar': "tutorialSidebar"
      },
      {
        path: '/utils/',
        component: ComponentCreator('/utils/','968'),
        exact: true,
        'sidebar': "tutorialSidebar"
      }
    ]
  },
  {
    path: '*',
    component: ComponentCreator('*')
  }
];
