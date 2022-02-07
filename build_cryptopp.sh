PREFIX_AND="TEMP_AND"
PREFIX_IOS="TEMP_CRYPTOPP_IOS"

function build_cryptopp_android
{
    ANDROID_API="$1" ANDROID_CPU="$1" source TestScripts/setenv-android.sh
    make -f GNUmakefile-cross
    make install -f GNUmakefile-cross PREFIX="$PREFIX_AND"
    mkdir -p "../cpp/android/$2/include/"
    mv "$PREFIX_AND/lib/libcryptopp.a" "../cpp/android/$2/libcryptopp.a"
    mv "$PREFIX_AND/include/cryptopp" "../cpp/android/$2/include"
}

function build_cryptopp_ios
{
    IOS_SDK="$1" IOS_CPU="$2" source setenv-ios.sh
    make -f GNUmakefile-cross
    make install -f GNUmakefile-cross PREFIX="$PREFIX_IOS"
    mv "$PREFIX_IOS/lib/libcryptopp.a" "../cpp/ios/libcryptopp_$2.a"
    mv "$PREFIX_IOS/include/cryptopp" "../cpp/ios/include"
}

# #########################################
# #####            Android            #####
# #########################################

# Clean old data
rm -rf "cpp/android"

pushd "cryptopp"
make clean

# Build for all architectures
build_cryptopp_android 21 armeabi-v7a
make clean

build_cryptopp_android 21 arm64-v8a
make clean

build_cryptopp_android 21 x86
make clean

build_cryptopp_android 21 x86_64
make clean

rm -rf "$PREFIX_AND"
popd

# #########################################
# #####              iOS              #####
# #########################################

# Clean old data
rm -rf "cpp/ios"

pushd "cryptopp"
make clean

# Bug fix => https://github.com/weidai11/cryptopp/issues/1074
cp -f "TestScripts/setenv-ios.sh" "setenv-ios.sh"
search="-DNDEBUG"
replace="-DNDEBUG -DCRYPTOPP_DISABLE_ARM_CRC32"
sed -i  -e "s/$search/$replace/g" "setenv-ios.sh"

mkdir -p "../cpp/ios/include"

# Build for physical devices
build_cryptopp_ios iPhoneOS arm64
make clean

# Build for simulator
build_cryptopp_ios iPhoneSimulator i386
make clean

# Build for simulator
build_cryptopp_ios iPhoneSimulator x86_64
make clean

rm -rf "$PREFIX_IOS"
popd