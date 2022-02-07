# builds fat library before pod is installed 
# to prevent having a file that's too large
lipo -create cpp/ios/libcryptopp_arm64.a \
             cpp/ios/libcryptopp_i386.a \
             cpp/ios/libcryptopp_x86_64.a \
     -output cpp/ios/libcryptopp.a
