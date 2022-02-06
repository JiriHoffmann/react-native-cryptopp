

PREFIX_AND="TEMP_AND"

function build_cryptopp_android
{
    ANDROID_API="$1" ANDROID_CPU="$1" source TestScripts/setenv-android.sh
    make -f GNUmakefile-cross distclean
    make -f GNUmakefile-cross
    make install -f GNUmakefile-cross PREFIX="$PREFIX_AND"
    mkdir -p "../cpp/android/$2/include/"
    mv "$PREFIX_AND/lib/libcryptopp.a" "../cpp/android/$2/libcryptopp.a"
    mv "$PREFIX_AND/include/cryptopp" "../cpp/android/$2/include"
}


#########################################
#####            Prepare            #####
#########################################

# Cleanup
rm -rf "cpp/android"

# #########################################
# #####            Android            #####
# #########################################

pushd "cryptopp"

build_cryptopp_android 21 armeabi-v7a
make clean

build_cryptopp_android 21 arm64-v8a
make clean

build_cryptopp_android 21 x86
make clean

build_cryptopp_android 21 x86_64
make clean

popd

# #########################################
# #####            Cleanup            #####
# #########################################

rm -rf "cryptopp/$PREFIX_AND"
