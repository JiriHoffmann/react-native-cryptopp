"use strict";(self.webpackChunkcryptopp_docs=self.webpackChunkcryptopp_docs||[]).push([[79],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>m});var r=n(7294);function o(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function a(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?a(Object(n),!0).forEach((function(t){o(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):a(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},a=Object.keys(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var p=r.createContext({}),s=function(e){var t=r.useContext(p),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},c=function(e){var t=s(e.components);return r.createElement(p.Provider,{value:t},e.children)},d={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},u=r.forwardRef((function(e,t){var n=e.components,o=e.mdxType,a=e.originalType,p=e.parentName,c=l(e,["components","mdxType","originalType","parentName"]),u=s(n),m=o,y=u["".concat(p,".").concat(m)]||u[m]||d[m]||a;return n?r.createElement(y,i(i({ref:t},c),{},{components:n})):r.createElement(y,i({ref:t},c))}));function m(e,t){var n=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=n.length,i=new Array(a);i[0]=u;var l={};for(var p in t)hasOwnProperty.call(t,p)&&(l[p]=t[p]);l.originalType=e,l.mdxType="string"==typeof e?e:o,i[1]=l;for(var s=2;s<a;s++)i[s]=n[s];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}u.displayName="MDXCreateElement"},5150:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>p,contentTitle:()=>i,default:()=>d,frontMatter:()=>a,metadata:()=>l,toc:()=>s});var r=n(7462),o=(n(7294),n(3905));const a={sidebar_position:0,slug:"/"},i="Installation",l={unversionedId:"intro",id:"version-0.2.0/intro",title:"Installation",description:"Make sure Hermes is enabled in your project.",source:"@site/versioned_docs/version-0.2.0/intro.md",sourceDirName:".",slug:"/",permalink:"/react-native-cryptopp/0.2.0/",editUrl:"https://github.com/JiriHoffmann/react-native-cryptopp/docs/versioned_docs/version-0.2.0/intro.md",tags:[],version:"0.2.0",sidebarPosition:0,frontMatter:{sidebar_position:0,slug:"/"},sidebar:"tutorialSidebar",next:{title:"Crypto++ Support",permalink:"/react-native-cryptopp/0.2.0/support/"}},p={},s=[{value:"Optional: Using pre-compiled Crypto++ library",id:"optional-using-pre-compiled-crypto-library",level:3},{value:"Installation: iOS",id:"installation-ios",level:3},{value:"Installation: Android",id:"installation-android",level:3}],c={toc:s};function d(e){let{components:t,...n}=e;return(0,o.kt)("wrapper",(0,r.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"installation"},"Installation"),(0,o.kt)("p",null,"Make sure ",(0,o.kt)("a",{parentName:"p",href:"https://reactnative.dev/docs/hermes"},"Hermes")," is enabled in your project."),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash"},"npm install react-native-cryptopp\n# or\nyarn add react-native-cryptopp\n")),(0,o.kt)("p",null,"As mentioned in the ",(0,o.kt)("inlineCode",{parentName:"p"},"README"),", the Crypto++ library has to be compiled for all CPU architectures (4 on android, 3 on iOS) the first time it is used, then it is cached for subsequent builds."),(0,o.kt)("h3",{id:"optional-using-pre-compiled-crypto-library"},"Optional: Using pre-compiled Crypto++ library"),(0,o.kt)("p",null,"Pre-compiled Crypto++ libraries via GitHub Actions are available for iOS and Android. They can be downloaded manually from releases on GitHub or by running the following command:"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash"},"yarn node node_modules/react-native-cryptopp/scripts/download_cryptopp.js\n")),(0,o.kt)("p",null,"You can also add it as a ",(0,o.kt)("inlineCode",{parentName:"p"},"postinstall")," script in your ",(0,o.kt)("inlineCode",{parentName:"p"},"package.json")," file."),(0,o.kt)("h3",{id:"installation-ios"},"Installation: iOS"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash"},"cd ios && pod install\n# or\nnpx pod install\n# or add --verbose to see compilation output\ncd ios && pod install --verbose\n")),(0,o.kt)("p",null,"Make sure you ",(0,o.kt)("strong",{parentName:"p"},"DON't")," run the ",(0,o.kt)("inlineCode",{parentName:"p"},"android build")," and ",(0,o.kt)("inlineCode",{parentName:"p"},"pod install")," at the same time! Temporary compiled files are saved inside the cryptopp folder and will overwrite each other resulting in issues when they are combined into the final library."),(0,o.kt)("h3",{id:"installation-android"},"Installation: Android"),(0,o.kt)("p",null,"Crypto++ will be compiled when you build the Adroid app for the first time. You can check the following files for more information about the compilation process:"),(0,o.kt)("p",null,"Location from the root of the project: "),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre"},"node_modules/react-native-cryptopp/android/build/cryptopp_build.txt\n")),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre"},"node_modules/react-native-cryptopp/android/build/cryptopp_error.txt\n")),(0,o.kt)("h1",{id:"usage"},"Usage"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-js"},"import Cryptopp from 'react-native-cryptopp';\n\nconst hash = Cryptopp.hashFunctions.SHA1('Hello World');\n")))}d.isMDXComponent=!0}}]);