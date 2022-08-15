require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "react-native-cryptopp"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => "11.0" }
  s.source       = { :git => "https://github.com/JiriHoffmann/react-native-cryptopp.git", :tag => "#{s.version}" }

  s.source_files = "ios/**/*.{h,m,mm}" , "cpp/*.{h,hpp,cpp}", "cpp/cryptopp/*.h"

  s.prepare_command = "sh scripts/compile_cryptopp_ios.sh"
  s.ios.vendored_frameworks = [
    'cpp/ios/libcryptopp.xcframework', 
  ]

  s.dependency "React-callinvoker"
  s.dependency "React"
  s.dependency "React-Core"
end
