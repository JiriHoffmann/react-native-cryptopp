cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "cryptopp")
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 11)

file(GLOB CRYPTOPP_SOURCE "../cryptopp/*.h")

include_directories(
  ../cpp
  ../cryptopp
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
  ${CRYPTOPP_SOURCE}
  )

target_link_libraries(${PACKAGE_NAME})
