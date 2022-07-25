#!/bin/bash
TEMP_IOS="TEMP_IOS"
CWD=$(pwd -P)

# Do not compile if the library already exists
if [ -e "$CWD/cpp/ios/libcryptopp.xcframework" ]
then
    exit 0
fi

function build_cryptopp_ios
{
    IOS_SDK="$1" IOS_CPU="$2" source setenv-ios.sh

    make -f GNUmakefile-cross static
    make install -f GNUmakefile-cross PREFIX="$TEMP_IOS"

    # Create folder for each build target and copy over
    mkdir -p "$TEMP_IOS/lib/$1_$2/"
    mv "$TEMP_IOS/lib/libcryptopp.a" "$TEMP_IOS/lib/$1_$2/libcryptopp.a"
}

# #########################################
# #####           Prepare             #####
# #########################################
pushd "$CWD"
mkdir -p "cpp/cryptopp" "cpp/ios"
sh scripts/copy_pem_pack.sh

pushd "cryptopp"
make clean

# Copy over setup script to make some changes
cp -f "TestScripts/setenv-ios.sh" "setenv-ios.sh"

# Bug fix => https://github.com/weidai11/cryptopp/issues/1074
search="-DNDEBUG"
replace="-DNDEBUG -DCRYPTOPP_DISABLE_ARM_CRC32"
sed -i  -e "s/$search/$replace/g" setenv-ios.sh

# Bug fix => https://github.com/weidai11/cryptopp/issues/1113
# Causes crashes on iOS simulator, if you can't comile cryptopp
# comment out the following lines
search="-DCRYPTOPP_DISABLE_ASM"
replace="-DCRYPTOPP_DISABLE_SSSE3"
sed -i  -e "s/$search/$replace/g" setenv-ios.sh

# Add arm64 iPhoneSimulator
add='elif [[ "${IOS_SDK}" == "iPhoneSimulator" \&\& "${IOS_CPU}" == "arm64" ]]; then\n    MIN_VER=-miphonesimulator-version-min=6\n'
sed -i '' "174s/.*/$add/" setenv-ios.sh

# #########################################
# #####             Build             #####
# #########################################

# Build for physical devices
build_cryptopp_ios iPhoneOS arm64
make clean

# Build for simulator
build_cryptopp_ios iPhoneSimulator x86_64
make clean

build_cryptopp_ios iPhoneSimulator arm64
make clean

# Create fat lib
lipo -create "$TEMP_IOS/lib/iPhoneSimulator_x86_64/libcryptopp.a" \
             "$TEMP_IOS/lib/iPhoneSimulator_arm64/libcryptopp.a" \
     -output "$TEMP_IOS/lib/libcryptopp.a"

# Create xcframework
xcodebuild -create-xcframework -library "$TEMP_IOS/lib/libcryptopp.a" \
                               -library "$TEMP_IOS/lib/iPhoneOS_arm64/libcryptopp.a" \
                               -output  "$TEMP_IOS/lib/libcryptopp.xcframework"

# Move headers and framework
mv -f "$TEMP_IOS/include/cryptopp" "../cpp"
mv -f "$TEMP_IOS/lib/libcryptopp.xcframework" "../cpp/ios/libcryptopp.xcframework"

rm -rf "$TEMP_IOS"
popd
