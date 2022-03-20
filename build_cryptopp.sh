TEMP_AND="TEMP_AND"
TEMP_IOS="TEMP_CRYPTOPP_IOS"

# Note: headers for both platforms are the same except
# android has an additional header file: cpu_features.h

function copy_pem_pack
{
    cp "cryptopp-pem/pem_common.cpp" "cryptopp/pem_common.cpp"
    cp "cryptopp-pem/pem_common.h" "cryptopp/pem_common.h"

    cp "cryptopp-pem/pem_read.cpp" "cryptopp/pem_read.cpp"
    cp "cryptopp-pem/pem_write.cpp" "cryptopp/pem_write.cpp"
    cp "cryptopp-pem/pem.h" "cryptopp/pem.h"

    cp "cryptopp-pem/x509cert.cpp" "cryptopp/x509cert.cpp"
    cp "cryptopp-pem/x509cert.h" "cryptopp/x509cert.h"
}

function clean_pem_pack
{
    rm "cryptopp/pem_common.cpp"
    rm "cryptopp/pem_common.h"

    rm "cryptopp/pem_read.cpp"
    rm "cryptopp/pem_write.cpp"
    rm "cryptopp/pem.h"

    rm "cryptopp/x509cert.cpp"
    rm "cryptopp/x509cert.h"
}

function build_cryptopp_android
{
    ANDROID_API="$1" ANDROID_CPU="$1" source TestScripts/setenv-android.sh
    make -f GNUmakefile-cross static
    make install -f GNUmakefile-cross PREFIX="$TEMP_AND"
    # copy headers
    mv "$TEMP_AND/include/cryptopp" "../cpp" 
    # zip and copy lib - size is too big for github
    pushd "$TEMP_AND/lib/"
    mv "libcryptopp.a" "libcryptopp_$2.a" 
    zip "../../../cpp/android/libcryptopp_$2.zip" "libcryptopp_$2.a" 
    popd

}

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
# rm -rf "cpp/cryptopp" # clean headers
# mkdir "cpp/cryptopp"
copy_pem_pack

# #########################################
# #####            Android            #####
# #########################################

# Clean old data
# rm -rf "cpp/android"
# mkdir "cpp/android"

# pushd "cryptopp"
# make clean

# # Build for all architectures
# build_cryptopp_android 30 armeabi-v7a
# make clean

# build_cryptopp_android 30 arm64-v8a
# make clean

# build_cryptopp_android 30 x86
# make clean

# build_cryptopp_android 30 x86_64
# make clean

# rm -rf "$TEMP_AND"
# popd

# #########################################
# #####              iOS              #####
# #########################################

# Clean old data and create folders
rm -rf "cpp/ios"
mkdir "cpp/ios"

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
build_cryptopp_ios iPhoneSimulator i386
make clean

# Build for simulator
build_cryptopp_ios iPhoneSimulator x86_64
make clean

rm -rf "$TEMP_IOS"
popd

# #########################################
# #####           Clean-up            #####
# #########################################
clean_pem_pack
