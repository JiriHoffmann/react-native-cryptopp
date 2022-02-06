cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "rncryptopp")
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 11)

include_directories(
  ../cpp
  ${CRYPTOPP_HEADERS}
  "${NODE_MODULES_DIR}/react-native/React"
  "${NODE_MODULES_DIR}/react-native/React/Base"
  "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
)

add_library(
  ${PACKAGE_NAME}
  SHARED
  "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp"
  ../cpp/react-native-cryptopp.cpp
  ../cpp/react-native-cryptopp.h
  cpp-adapter.cpp
)

add_library(cryptopp STATIC IMPORTED)

set_target_properties(
  # Target library
  cryptopp
  # Define property location
  PROPERTIES IMPORTED_LOCATION
  # Path to the library. Must be full path.
  ${PROJECT_SOURCE_DIR}/../cpp/android/${CMAKE_ANDROID_ARCH_ABI}/libcryptopp.a
)

# Location of the headers for the library
include_directories(
  ../cpp/android/${CMAKE_ANDROID_ARCH_ABI}/include
)

set_target_properties(cryptopp PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PACKAGE_NAME} cryptopp)
