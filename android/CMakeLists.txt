cmake_minimum_required(VERSION 3.9.0)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)
set (PACKAGE_NAME "rncryptopp")
set (BUILD_DIR ./build)

file(GLOB RN_CRYPTOPP_FILES "../cpp/*.cpp")
file(GLOB RN_CRYPTOPP_HEADERS "../cpp")
file(GLOB LIBRN_DIR "${BUILD_DIR}/react-native-0*/jni/${ANDROID_ABI}")

# Add headers
include_directories(
  ${PACKAGE_NAME}
  "${NODE_MODULES_DIR}/react-native/React"
  "${NODE_MODULES_DIR}/react-native/React/Base"
  "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"

  # rncryptopp headers
  # Import manually to make sure the order is correct
  "../cpp/helpers.h"
  "../cpp/utils.h"
  ${RN_CRYPTOPP_HEADERS}

  # Crypto++ headers
  ../cpp/android/${CMAKE_ANDROID_ARCH_ABI}/include
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
          ./cpp-adapter.cpp
  )
else()
  set (JSI_LIB "")
  add_library(
          ${PACKAGE_NAME}
          SHARED
          ${RN_CRYPTOPP_FILES}
          ${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp
          ./cpp-adapter.cpp
  )
endif()

# Find JNI
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
  ${PROJECT_SOURCE_DIR}/../cpp/android/${CMAKE_ANDROID_ARCH_ABI}/libcryptopp.a
)

# Link JNI, JSI, LOG_LIB, and cryptopp
target_link_libraries(
  ${PACKAGE_NAME}
  ${REACT_NATIVE_JNI_LIB}
  ${JSI_LIB}
  ${LOG_LIB}
  cryptopp
  android
)
