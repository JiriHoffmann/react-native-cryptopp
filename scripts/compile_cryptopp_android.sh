#!/bin/bash
ANDROID_PLATFORM=$1
ANDROID_CPU=$2
CWD=$3
export ANDROID_SDK_ROOT=$4
export ANDROID_NDK_ROOT=$5

TEMP_AND="TEMP_AND"
ANDROID_API="${ANDROID_PLATFORM: -2}"

echo "Root directory for react-native-cryptopp: $CWD"
echo "Using API:${ANDROID_API} and CPU:${ANDROID_CPU}"
echo "Android SDK: $ANDROID_SDK_ROOT"
echo "Android NDK: $ANDROID_NDK_ROOT"
echo "Crypto++ Compilation output: \n\n\n"

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

# Build for all architectures
build_cryptopp_android ${ANDROID_API} ${ANDROID_CPU}
make clean

rm -rf "$TEMP_AND"
popd
popd