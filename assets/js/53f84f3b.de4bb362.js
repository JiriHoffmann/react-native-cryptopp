"use strict";(self.webpackChunkcryptopp_docs=self.webpackChunkcryptopp_docs||[]).push([[9964],{3905:(e,t,n)=>{n.d(t,{Zo:()=>l,kt:()=>d});var r=n(7294);function o(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function a(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function c(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?a(Object(n),!0).forEach((function(t){o(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):a(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function s(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},a=Object.keys(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var i=r.createContext({}),p=function(e){var t=r.useContext(i),n=t;return e&&(n="function"==typeof e?e(t):c(c({},t),e)),n},l=function(e){var t=p(e.components);return r.createElement(i.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},y=r.forwardRef((function(e,t){var n=e.components,o=e.mdxType,a=e.originalType,i=e.parentName,l=s(e,["components","mdxType","originalType","parentName"]),y=p(n),d=o,h=y["".concat(i,".").concat(d)]||y[d]||u[d]||a;return n?r.createElement(h,c(c({ref:t},l),{},{components:n})):r.createElement(h,c({ref:t},l))}));function d(e,t){var n=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=n.length,c=new Array(a);c[0]=y;var s={};for(var i in t)hasOwnProperty.call(t,i)&&(s[i]=t[i]);s.originalType=e,s.mdxType="string"==typeof e?e:o,c[1]=s;for(var p=2;p<a;p++)c[p]=n[p];return r.createElement.apply(null,c)}return r.createElement.apply(null,n)}y.displayName="MDXCreateElement"},3848:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>i,contentTitle:()=>c,default:()=>u,frontMatter:()=>a,metadata:()=>s,toc:()=>p});var r=n(7462),o=(n(7294),n(3905));const a={sidebar_position:1},c="Asynchronous Functionality",s={unversionedId:"async/async",id:"async/async",title:"Asynchronous Functionality",description:"Cryptopp.async provides exactly the same functionality to the synchronous counterparts, but with the ability to run all computations asynchronously offloaded to another thread. Even complex computations such as creating an RSA key pair can be done without a single FPS drop in the JS thread.",source:"@site/docs/async/async.md",sourceDirName:"async",slug:"/async/",permalink:"/react-native-cryptopp/next/async/",editUrl:"https://github.com/JiriHoffmann/react-native-cryptopp/docs/docs/async/async.md",tags:[],version:"current",sidebarPosition:1,frontMatter:{sidebar_position:1},sidebar:"tutorialSidebar",previous:{title:"Crypto++ Support",permalink:"/react-native-cryptopp/next/support/"},next:{title:"AES",permalink:"/react-native-cryptopp/next/aes-and-aes-candidates/aes"}},i={},p=[],l={toc:p};function u(e){let{components:t,...n}=e;return(0,o.kt)("wrapper",(0,r.Z)({},l,n,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"asynchronous-functionality"},"Asynchronous Functionality"),(0,o.kt)("p",null,"Cryptopp.async provides exactly the same functionality to the synchronous counterparts, but with the ability to run all computations asynchronously offloaded to another thread. Even complex computations such as creating an RSA key pair can be done without a single FPS drop in the JS thread. "),(0,o.kt)("p",null,"All functions have the exact same signature but return a Promise."),(0,o.kt)("p",null,"Note: Progressive hashing does not have asynchronous functions."),(0,o.kt)("h1",{id:"example"},"Example"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-js"},"// Synchronous - returns string\nconst hash_result = Cryptopp.hash.SHA1('Hello World'); \n\n// Asynchronous - returns Promise<string>\nconst hash_result2 = await Cryptopp.async.hash.SHA1('Hello World'); \n")))}u.isMDXComponent=!0}}]);