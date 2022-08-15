cmake_minimum_required(VERSION 3.9.0)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)
set (PACKAGE_NAME "rncryptopp")
set (BUILD_DIR build)

# Compile Crypto++
# Must have full paths
execute_process(
        COMMAND chmod u+x ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/compile_cryptopp_android.sh
        OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/build/cryptopp_chmod.txt
        ERROR_FILE ${CMAKE_CURRENT_SOURCE_DIR}/build/cryptopp_chmod.txt
)
execute_process(
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/compile_cryptopp_android.sh
        ${ANDROID_PLATFORM} "${CMAKE_CURRENT_SOURCE_DIR}/../" ${SDK_ROOT_PATH} ${NDK_ROOT_PATH}
        OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/build/cryptopp_build.txt
        ERROR_FILE ${CMAKE_CURRENT_SOURCE_DIR}/build/cryptopp_error.txt
)

# TODO: find a way to include headers only,
# TODO: this includes everything,
# TODO: even headers in cpp/cryptopp
file(GLOB RN_CRYPTOPP_HEADERS "../cpp")
file(GLOB RN_CRYPTOPP_FILES "../cpp/*.cpp")
file(GLOB RN_CRYPTOPP_HO_FILES "../cpp/host_objects/*.cpp")
file(GLOB RN_CRYPTOPP_HPP_FILES "../cpp/*.hpp")
file(GLOB LIBRN_DIR "${BUILD_DIR}/react-native-0*/jni/${ANDROID_ABI}")
file(GLOB LIBFBJNI_INCLUDE_DIR "${BUILD_DIR}/fbjni-*-headers.jar/")

# Add headers
include_directories(
  ${PACKAGE_NAME}
  "${NODE_MODULES_DIR}/react-native/React"
  "${NODE_MODULES_DIR}/react-native/React/Base"
  "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
  "${NODE_MODULES_DIR}/react-native/ReactCommon/callinvoker"
  "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni"
  "${NODE_MODULES_DIR}/hermes-engine/android/include/"
  ${RN_CRYPTOPP_HEADERS}
)

# Find JSI on React Native 0.66.x and above
# else manually add JSI on React Native 0.65.x and below
# and add all project source files
if (EXISTS "${LIBRN_DIR}/libjsi.so")
  find_library(
          JSI_LIB
          jsi
          PATHS ${LIBRN_DIR}
          NO_CMAKE_FIND_ROOT_PATH
  )
  add_library(
          ${PACKAGE_NAME}
          SHARED
          ${RN_CRYPTOPP_FILES}
          ${RN_CRYPTOPP_HPP_FILES}
          ${RN_CRYPTOPP_HO_FILES}
          ./cpp-adapter.cpp
  )
else()
  set (JSI_LIB "")
  add_library(
          ${PACKAGE_NAME}
          SHARED
          ${RN_CRYPTOPP_FILES}
          ${RN_CRYPTOPP_HPP_FILES}
          ${RN_CRYPTOPP_HO_FILES}
          ${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp
          ./cpp-adapter.cpp
  )
endif()


target_include_directories(
        ${PACKAGE_NAME}
        PRIVATE
        # --- fbjni ---
        "${LIBFBJNI_INCLUDE_DIR}"
        # --- React Native ---
        "${NODE_MODULES_DIR}/react-native/React"
        "${NODE_MODULES_DIR}/react-native/React/Base"
        "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/jni"
        "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni"
        "${NODE_MODULES_DIR}/react-native/ReactCommon"
        "${NODE_MODULES_DIR}/react-native/ReactCommon/callinvoker"
        "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
        "${NODE_MODULES_DIR}/hermes-engine/android/include/"

)

# Find JNI
find_library(
        FBJNI_LIB
        fbjni
        PATHS ${LIBRN_DIR}
        NO_CMAKE_FIND_ROOT_PATH
)
 find_library(
         REACT_NATIVE_JNI_LIB
         reactnativejni
         PATHS ${LIBRN_DIR}
         NO_CMAKE_FIND_ROOT_PATH
 )

# Find LOG_LIB
find_library(
        LOG_LIB
        log
)

# Add cryptopp
add_library(cryptopp STATIC IMPORTED)
set_target_properties(
  # Target library
  cryptopp
  # Define property location
  PROPERTIES IMPORTED_LOCATION
  # Path to the library. Must be full path.
  ${PROJECT_SOURCE_DIR}/../cpp/android/libcryptopp_${ANDROID_ABI}.a
)

# Link JNI, JSI, LOG_LIB, and cryptopp
target_link_libraries(
  ${PACKAGE_NAME}
  cryptopp
  ${REACT_NATIVE_JNI_LIB}
  ${JSI_LIB}
  ${LOG_LIB}
  ${FBJNI_LIB}
  android
)
