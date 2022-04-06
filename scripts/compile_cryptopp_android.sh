#!/bin/bash
ANDROID_PLATFORM=$1
ANDROID_API="${ANDROID_PLATFORM: -2}" # from android-21 to 21
CWD=$2 #Path to the root of the project
export ANDROID_SDK_ROOT=$3
export ANDROID_NDK_ROOT=$4
TEMP_AND="TEMP_AND"

# Do not compile if the library already exists
if [[ -e "$CWD/cpp/android/libcryptopp_arm64-v8a.a" && 
     -e "$CWD/cpp/android/libcryptopp_armeabi-v7a.a" && 
     -e "$CWD/cpp/android/libcryptopp_x86_64.a" &&
     -e "$CWD/cpp/android/libcryptopp_x86.a" ]]
then
    exit 0
fi

echo "Root directory for react-native-cryptopp: $CWD"
echo "Using API:${ANDROID_API}"
echo "Android SDK: $ANDROID_SDK_ROOT"
echo "Android NDK: $ANDROID_NDK_ROOT"
echo -e "Crypto++ Compilation output: \n\n\n"

function build_cryptopp_android
{
    ANDROID_API="$1" ANDROID_CPU="$2" source TestScripts/setenv-android.sh
    make -f GNUmakefile-cross static
    make install -f GNUmakefile-cross PREFIX="$TEMP_AND"
    mv "$TEMP_AND/lib/libcryptopp.a" "../cpp/android/libcryptopp_$2.a"
    mv -f "$TEMP_AND/include/cryptopp" "../cpp"
}

# # #########################################
# # #####           Prepare             #####
# # #########################################
pushd "$CWD"
mkdir -p "cpp/cryptopp" "cpp/android"
sh scripts/copy_pem_pack.sh

# # #########################################
# # #####            Android            #####
# # #########################################

pushd "cryptopp"
make clean

# Compile for all architectures
build_cryptopp_android ${ANDROID_API} armeabi-v7a
make clean

build_cryptopp_android ${ANDROID_API} arm64-v8a
make clean

build_cryptopp_android ${ANDROID_API} x86
make clean

build_cryptopp_android ${ANDROID_API} x86_64
make clean

rm -rf "$TEMP_AND"
popd
popd