"use strict";(self.webpackChunkcryptopp_docs=self.webpackChunkcryptopp_docs||[]).push([[9798],{3905:(e,t,a)=>{a.d(t,{Zo:()=>o,kt:()=>k});var r=a(7294);function n(e,t,a){return t in e?Object.defineProperty(e,t,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[t]=a,e}function l(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,r)}return a}function i(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?l(Object(a),!0).forEach((function(t){n(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):l(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}function p(e,t){if(null==e)return{};var a,r,n=function(e,t){if(null==e)return{};var a,r,n={},l=Object.keys(e);for(r=0;r<l.length;r++)a=l[r],t.indexOf(a)>=0||(n[a]=e[a]);return n}(e,t);if(Object.getOwnPropertySymbols){var l=Object.getOwnPropertySymbols(e);for(r=0;r<l.length;r++)a=l[r],t.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(n[a]=e[a])}return n}var d=r.createContext({}),s=function(e){var t=r.useContext(d),a=t;return e&&(a="function"==typeof e?e(t):i(i({},t),e)),a},o=function(e){var t=s(e.components);return r.createElement(d.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},m=r.forwardRef((function(e,t){var a=e.components,n=e.mdxType,l=e.originalType,d=e.parentName,o=p(e,["components","mdxType","originalType","parentName"]),m=s(a),k=n,c=m["".concat(d,".").concat(k)]||m[k]||u[k]||l;return a?r.createElement(c,i(i({ref:t},o),{},{components:a})):r.createElement(c,i({ref:t},o))}));function k(e,t){var a=arguments,n=t&&t.mdxType;if("string"==typeof e||n){var l=a.length,i=new Array(l);i[0]=m;var p={};for(var d in t)hasOwnProperty.call(t,d)&&(p[d]=t[d]);p.originalType=e,p.mdxType="string"==typeof e?e:n,i[1]=p;for(var s=2;s<l;s++)i[s]=a[s];return r.createElement.apply(null,i)}return r.createElement.apply(null,a)}m.displayName="MDXCreateElement"},6384:(e,t,a)=>{a.r(t),a.d(t,{assets:()=>d,contentTitle:()=>i,default:()=>u,frontMatter:()=>l,metadata:()=>p,toc:()=>s});var r=a(7462),n=(a(7294),a(3905));const l={sidebar_position:1},i="RSA",p={unversionedId:"public-key-cryptography/rsa",id:"version-0.2.0/public-key-cryptography/rsa",title:"RSA",description:"This library uses the Cryptop++ PEM_PACK to parse and store RSA keys in the PEM format.",source:"@site/versioned_docs/version-0.2.0/public-key-cryptography/rsa.md",sourceDirName:"public-key-cryptography",slug:"/public-key-cryptography/rsa",permalink:"/react-native-cryptopp/0.2.0/public-key-cryptography/rsa",editUrl:"https://github.com/JiriHoffmann/react-native-cryptopp/docs/versioned_docs/version-0.2.0/public-key-cryptography/rsa.md",tags:[],version:"0.2.0",sidebarPosition:1,frontMatter:{sidebar_position:1},sidebar:"tutorialSidebar",previous:{title:"WHIRLPOOL",permalink:"/react-native-cryptopp/0.2.0/hash-functions/whirlpool"},next:{title:"HDKF",permalink:"/react-native-cryptopp/0.2.0/padding-schemes/hkdf"}},d={},s=[{value:"Generate Key Pair",id:"generate-key-pair",level:2},{value:"Returns: Object containing the public and private keys, as well as the parameters used to generate the keys.",id:"returns-object-containing-the-public-and-private-keys-as-well-as-the-parameters-used-to-generate-the-keys",level:4},{value:"Encrypt",id:"encrypt",level:2},{value:"Parameters",id:"parameters",level:4},{value:"Returns: <code>base64-encoded string</code>",id:"returns-base64-encoded-string",level:4},{value:"Decrypt",id:"decrypt",level:2},{value:"Parameters",id:"parameters-1",level:4},{value:"Returns: <code>string</code>",id:"returns-string",level:4},{value:"Sign",id:"sign",level:2},{value:"Parameters",id:"parameters-2",level:4},{value:"Returns: <code>base64-encoded string</code>",id:"returns-base64-encoded-string-1",level:4},{value:"Verify",id:"verify",level:2},{value:"Parameters",id:"parameters-3",level:4},{value:"Returns: <code>true</code> if the signature is valid, <code>false</code> otherwise.",id:"returns-true-if-the-signature-is-valid-false-otherwise",level:4},{value:"Recover",id:"recover",level:2},{value:"Parameters",id:"parameters-4",level:4},{value:"Returns: <code>string</code>",id:"returns-string-1",level:4},{value:"Throws error if the signature doesn&#39;t match the key",id:"throws-error-if-the-signature-doesnt-match-the-key",level:4}],o={toc:s};function u(e){let{components:t,...a}=e;return(0,n.kt)("wrapper",(0,r.Z)({},o,a,{components:t,mdxType:"MDXLayout"}),(0,n.kt)("h1",{id:"rsa"},"RSA"),(0,n.kt)("p",null,"This library uses the ",(0,n.kt)("a",{parentName:"p",href:"https://github.com/noloader/cryptopp-pem"},"Cryptop++ PEM_PACK")," to parse and store RSA keys in the PEM format."),(0,n.kt)("h2",{id:"generate-key-pair"},"Generate Key Pair"),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-js"},"const rsa_keypair = Cryptopp.RSA.generateKeyPair(2048);\n")),(0,n.kt)("h4",{id:"returns-object-containing-the-public-and-private-keys-as-well-as-the-parameters-used-to-generate-the-keys"},"Returns: Object containing the public and private keys, as well as the parameters used to generate the keys."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-json"},'{\n    public: "...",\n    private: "...",\n    params: {\n        n: "...",\n        p:"...",\n        q:"...",\n        d:"...",\n        e:"...",\n    },\n};\n')),(0,n.kt)("p",null,"Example of a returned public/private key:"),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre"},"-----BEGIN FOO BAR KEY-----\nMIIBgjAcBgoqhkiG9w0BDAEDMA4ECKZesfWLQOiDAgID6ASCAWBu7izm8N4V\n2puRO/Mdt+Y8ceywxiC0cE57nrbmvaTSvBwTg9b/xyd8YC6QK7lrhC9Njgp/\n...\n-----END FOO BAR KEY-----\n")),(0,n.kt)("h2",{id:"encrypt"},"Encrypt"),(0,n.kt)("p",null,"Encrypts a message using the public key."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-js"},"const publicKey = ... // obtained from second party\nconst encrypted = Cryptopp.RSA.encrypt(data, publicKey, 'OAEP_SHA1');\n")),(0,n.kt)("h4",{id:"parameters"},"Parameters"),(0,n.kt)("table",null,(0,n.kt)("thead",{parentName:"table"},(0,n.kt)("tr",{parentName:"thead"},(0,n.kt)("th",{parentName:"tr",align:null},"Parameter"),(0,n.kt)("th",{parentName:"tr",align:null},"Type"),(0,n.kt)("th",{parentName:"tr",align:null},"Required"))),(0,n.kt)("tbody",{parentName:"table"},(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"data"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"string")," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},"ArrayBuffer")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"publicKey"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"string")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"encryptionScheme"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},'"OAEP_SHA1"')," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"OAEP_SHA256"')," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PKCS1v15"')),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")))),(0,n.kt)("h4",{id:"returns-base64-encoded-string"},"Returns: ",(0,n.kt)("inlineCode",{parentName:"h4"},"base64-encoded string")),(0,n.kt)("h2",{id:"decrypt"},"Decrypt"),(0,n.kt)("p",null,"Decrypts a message using the private key."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-js"},"const rsa_keypair = ... // some locally stored keypair\nconst encryptedData = Cryptopp.RSA.encrypt(data, rsa_keypair.private, 'OAEP_SHA1');\n")),(0,n.kt)("h4",{id:"parameters-1"},"Parameters"),(0,n.kt)("table",null,(0,n.kt)("thead",{parentName:"table"},(0,n.kt)("tr",{parentName:"thead"},(0,n.kt)("th",{parentName:"tr",align:null},"Parameter"),(0,n.kt)("th",{parentName:"tr",align:null},"Type"),(0,n.kt)("th",{parentName:"tr",align:null},"Required"))),(0,n.kt)("tbody",{parentName:"table"},(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"data"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"base64-encoded string")," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},"ArrayBuffer")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"privateKey"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"string")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"encryptionScheme"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},'"OAEP_SHA1"')," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"OAEP_SHA256"')," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PKCS1v15"')),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")))),(0,n.kt)("h4",{id:"returns-string"},"Returns: ",(0,n.kt)("inlineCode",{parentName:"h4"},"string")),(0,n.kt)("h2",{id:"sign"},"Sign"),(0,n.kt)("p",null,"Signs a message with a private key to ensure authenticity."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-js"},"const rsa_keypair = ... // some locally stored keypair\nconst signedData = Cryptopp.RSA.sign(encryptedData, rsa_keypair.private, 'PKCS1v15_SHA1');\n")),(0,n.kt)("h4",{id:"parameters-2"},"Parameters"),(0,n.kt)("table",null,(0,n.kt)("thead",{parentName:"table"},(0,n.kt)("tr",{parentName:"thead"},(0,n.kt)("th",{parentName:"tr",align:null},"Parameter"),(0,n.kt)("th",{parentName:"tr",align:null},"Type"),(0,n.kt)("th",{parentName:"tr",align:null},"Required"))),(0,n.kt)("tbody",{parentName:"table"},(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"data"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"string")," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},"ArrayBuffer")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"privateKey"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"string")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"signatureScheme"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},'"PKCS1v15_SHA1"'),"  ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PKCS1v15_SHA256"'),"  ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PSSR_SHA1"'),"   ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PSSR_SHA256"'),"  ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PSSR_Whirlpool"')),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")))),(0,n.kt)("p",null,(0,n.kt)("inlineCode",{parentName:"p"},"Note:")," Crypto++ supports two broad categories of digital signatures: Signature Schemes with Appendix (PKCS1v15_SHA1 and PKCS1v15_SHA256) and Signature Schemes with Recovery (PSSR_SHA1, PSSR_SHA256, and PSSR_Whirlpool)."),(0,n.kt)("p",null,"A signature scheme with appendix requires the verifier to have three items: the public key, the message, and the signature. Can be verified using the ",(0,n.kt)("inlineCode",{parentName:"p"},"Cryptopp.RSA.verify")," function."),(0,n.kt)("p",null,"A signature scheme with recovery requires only the public key and signature - the message is recovered from the signature. Can be recovered using the ",(0,n.kt)("inlineCode",{parentName:"p"},"Cryptopp.RSA.recover")," function."),(0,n.kt)("h4",{id:"returns-base64-encoded-string-1"},"Returns: ",(0,n.kt)("inlineCode",{parentName:"h4"},"base64-encoded string")),(0,n.kt)("h2",{id:"verify"},"Verify"),(0,n.kt)("p",null,"Valides signature of a message."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-js"},"const data = ...\nconst dataSignature = ...\nconst publicKey = ... // obtained from second party\nconst isSignatureValid = Cryptopp.RSA.verify(signedData, publicKey, 'PKCS1v15_SHA1', dataSignature);\n")),(0,n.kt)("h4",{id:"parameters-3"},"Parameters"),(0,n.kt)("table",null,(0,n.kt)("thead",{parentName:"table"},(0,n.kt)("tr",{parentName:"thead"},(0,n.kt)("th",{parentName:"tr",align:null},"Parameter"),(0,n.kt)("th",{parentName:"tr",align:null},"Type"),(0,n.kt)("th",{parentName:"tr",align:null},"Required"))),(0,n.kt)("tbody",{parentName:"table"},(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"data"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"base64-encoded string")," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},"ArrayBuffer")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"publicKey"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"string")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"signatureScheme"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},'"PKCS1v15_SHA1"')," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PKCS1v15_SHA256"')),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")))),(0,n.kt)("h4",{id:"returns-true-if-the-signature-is-valid-false-otherwise"},"Returns: ",(0,n.kt)("inlineCode",{parentName:"h4"},"true")," if the signature is valid, ",(0,n.kt)("inlineCode",{parentName:"h4"},"false")," otherwise."),(0,n.kt)("h2",{id:"recover"},"Recover"),(0,n.kt)("p",null,"Recovers the message from the signature using the public key."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-js"},"// In this case, data has to be signed with PSSR and will be then distributed as the message\nconst data = ...\nconst rsa_keypair = ... // some locally stored keypair\nconst signature = Cryptopp.RSA.sign(data, rsa_keypair.private, 'PSSR_SHA1');\n\n// Recipient can now verify the signature and recover the message\nconst publicKey = ... // obtained from second party\ntry {\n    const recoveredData = Cryptopp.RSA.recover(signature, publicKey, 'PSSR_SHA1');\n} catch (e) {\n    // handle error if signature doens't match the key\n}\n")),(0,n.kt)("h4",{id:"parameters-4"},"Parameters"),(0,n.kt)("table",null,(0,n.kt)("thead",{parentName:"table"},(0,n.kt)("tr",{parentName:"thead"},(0,n.kt)("th",{parentName:"tr",align:null},"Parameter"),(0,n.kt)("th",{parentName:"tr",align:null},"Type"),(0,n.kt)("th",{parentName:"tr",align:null},"Required"))),(0,n.kt)("tbody",{parentName:"table"},(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"signature"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"base64-encoded string")," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},"ArrayBuffer")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"publicKey"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},"string")),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"signatureScheme"),(0,n.kt)("td",{parentName:"tr",align:null},(0,n.kt)("inlineCode",{parentName:"td"},'"PSSR_SHA1"')," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PSSR_SHA256"')," ",(0,n.kt)("br",null)," ",(0,n.kt)("inlineCode",{parentName:"td"},'"PSSR_Whirlpool"')),(0,n.kt)("td",{parentName:"tr",align:null},"\u2705")))),(0,n.kt)("h4",{id:"returns-string-1"},"Returns: ",(0,n.kt)("inlineCode",{parentName:"h4"},"string")),(0,n.kt)("h4",{id:"throws-error-if-the-signature-doesnt-match-the-key"},"Throws error if the signature doesn't match the key"))}u.isMDXComponent=!0}}]);