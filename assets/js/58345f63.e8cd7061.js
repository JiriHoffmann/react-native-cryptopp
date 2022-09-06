"use strict";(self.webpackChunkcryptopp_docs=self.webpackChunkcryptopp_docs||[]).push([[5823],{3905:(e,t,r)=>{r.d(t,{Zo:()=>c,kt:()=>m});var n=r(7294);function a(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function l(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function i(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?l(Object(r),!0).forEach((function(t){a(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):l(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function o(e,t){if(null==e)return{};var r,n,a=function(e,t){if(null==e)return{};var r,n,a={},l=Object.keys(e);for(n=0;n<l.length;n++)r=l[n],t.indexOf(r)>=0||(a[r]=e[r]);return a}(e,t);if(Object.getOwnPropertySymbols){var l=Object.getOwnPropertySymbols(e);for(n=0;n<l.length;n++)r=l[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(a[r]=e[r])}return a}var p=n.createContext({}),s=function(e){var t=n.useContext(p),r=t;return e&&(r="function"==typeof e?e(t):i(i({},t),e)),r},c=function(e){var t=s(e.components);return n.createElement(p.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},d=n.forwardRef((function(e,t){var r=e.components,a=e.mdxType,l=e.originalType,p=e.parentName,c=o(e,["components","mdxType","originalType","parentName"]),d=s(r),m=a,b=d["".concat(p,".").concat(m)]||d[m]||u[m]||l;return r?n.createElement(b,i(i({ref:t},c),{},{components:r})):n.createElement(b,i({ref:t},c))}));function m(e,t){var r=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var l=r.length,i=new Array(l);i[0]=d;var o={};for(var p in t)hasOwnProperty.call(t,p)&&(o[p]=t[p]);o.originalType=e,o.mdxType="string"==typeof e?e:a,i[1]=o;for(var s=2;s<l;s++)i[s]=r[s];return n.createElement.apply(null,i)}return n.createElement.apply(null,r)}d.displayName="MDXCreateElement"},7066:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>p,contentTitle:()=>i,default:()=>u,frontMatter:()=>l,metadata:()=>o,toc:()=>s});var n=r(7462),a=(r(7294),r(3905));const l={sidebar_position:2},i="BLAKE2b/BLAKE2s",o={unversionedId:"hash-functions/blake2",id:"hash-functions/blake2",title:"BLAKE2b/BLAKE2s",description:"BLAKE2b",source:"@site/docs/hash-functions/blake2.md",sourceDirName:"hash-functions",slug:"/hash-functions/blake2",permalink:"/react-native-cryptopp/next/hash-functions/blake2",editUrl:"https://github.com/JiriHoffmann/react-native-cryptopp/docs/docs/hash-functions/blake2.md",tags:[],version:"current",sidebarPosition:2,frontMatter:{sidebar_position:2},sidebar:"tutorialSidebar",previous:{title:"Progressive Hashing",permalink:"/react-native-cryptopp/next/hash-functions/create"},next:{title:"Keccak",permalink:"/react-native-cryptopp/next/hash-functions/keccak"}},p={},s=[{value:"BLAKE2b",id:"blake2b",level:2},{value:"Parameters",id:"parameters",level:4},{value:"Returns: <code>string</code>",id:"returns-string",level:4},{value:"BLAKE2s",id:"blake2s",level:2},{value:"Parameters",id:"parameters-1",level:4},{value:"Returns: <code>string</code>",id:"returns-string-1",level:4}],c={toc:s};function u(e){let{components:t,...r}=e;return(0,a.kt)("wrapper",(0,n.Z)({},c,r,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"blake2bblake2s"},"BLAKE2b/BLAKE2s"),(0,a.kt)("h2",{id:"blake2b"},"BLAKE2b"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-js"},"Cryptopp.hash.BLAKE2b(data);\n")),(0,a.kt)("h4",{id:"parameters"},"Parameters"),(0,a.kt)("table",null,(0,a.kt)("thead",{parentName:"table"},(0,a.kt)("tr",{parentName:"thead"},(0,a.kt)("th",{parentName:"tr",align:null},"Parameter"),(0,a.kt)("th",{parentName:"tr",align:null},"Type"),(0,a.kt)("th",{parentName:"tr",align:null},"Required"))),(0,a.kt)("tbody",{parentName:"table"},(0,a.kt)("tr",{parentName:"tbody"},(0,a.kt)("td",{parentName:"tr",align:null},"data"),(0,a.kt)("td",{parentName:"tr",align:null},(0,a.kt)("inlineCode",{parentName:"td"},"string")," ",(0,a.kt)("br",null)," ",(0,a.kt)("inlineCode",{parentName:"td"},"ArrayBuffer")),(0,a.kt)("td",{parentName:"tr",align:null},"\u2705")))),(0,a.kt)("h4",{id:"returns-string"},"Returns: ",(0,a.kt)("inlineCode",{parentName:"h4"},"string")),(0,a.kt)("h2",{id:"blake2s"},"BLAKE2s"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-js"},"Cryptopp.hash.BLAKE2s(data);\n")),(0,a.kt)("h4",{id:"parameters-1"},"Parameters"),(0,a.kt)("table",null,(0,a.kt)("thead",{parentName:"table"},(0,a.kt)("tr",{parentName:"thead"},(0,a.kt)("th",{parentName:"tr",align:null},"Parameter"),(0,a.kt)("th",{parentName:"tr",align:null},"Type"),(0,a.kt)("th",{parentName:"tr",align:null},"Required"))),(0,a.kt)("tbody",{parentName:"table"},(0,a.kt)("tr",{parentName:"tbody"},(0,a.kt)("td",{parentName:"tr",align:null},"data"),(0,a.kt)("td",{parentName:"tr",align:null},(0,a.kt)("inlineCode",{parentName:"td"},"string")," ",(0,a.kt)("br",null)," ",(0,a.kt)("inlineCode",{parentName:"td"},"ArrayBuffer")),(0,a.kt)("td",{parentName:"tr",align:null},"\u2705")))),(0,a.kt)("h4",{id:"returns-string-1"},"Returns: ",(0,a.kt)("inlineCode",{parentName:"h4"},"string")))}u.isMDXComponent=!0}}]);