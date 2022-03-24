#!/bin/bash

TEMP_IOS="TEMP_IOS"
CWD=$(pwd -P)

# Do not compile if the library already exists
if [ -e "$CWD/cpp/ios/libcryptopp.a" ]
then
    exit 0
fi

function build_cryptopp_ios
{
    IOS_SDK="$1" IOS_CPU="$2" source setenv-ios.sh
    make -f GNUmakefile-cross static
    make install -f GNUmakefile-cross PREFIX="$TEMP_IOS"
    mv "$TEMP_IOS/lib/libcryptopp.a" "../cpp/ios/libcryptopp_$2.a"
    mv "$TEMP_IOS/include/cryptopp" "../cpp"
}

# #########################################
# #####           Prepare             #####
# #########################################
pushd "$CWD"
mkdir -p "cpp/cryptopp" "cpp/ios"
sh scripts/copy_pem_pack.sh

# #########################################
# #####              iOS              #####
# #########################################

pushd "cryptopp"
make clean

# Bug fix => https://github.com/weidai11/cryptopp/issues/1074
cp -f "TestScripts/setenv-ios.sh" "setenv-ios.sh"
search="-DNDEBUG"
replace="-DNDEBUG -DCRYPTOPP_DISABLE_ARM_CRC32"
sed -i  -e "s/$search/$replace/g" "setenv-ios.sh"

# Build for physical devices
build_cryptopp_ios iPhoneOS arm64
make clean

# Build for simulator
build_cryptopp_ios iPhoneSimulator x86_64
make clean

rm -rf "$TEMP_IOS"
popd

# Create fat lib
lipo -create cpp/ios/libcryptopp_arm64.a \
             cpp/ios/libcryptopp_x86_64.a \
     -output cpp/ios/libcryptopp.a
popd