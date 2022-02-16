cmake_minimum_required(VERSION 3.9.0)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)
set (PACKAGE_NAME "rncryptopp")
set (BUILD_DIR ./build)

file(GLOB RN_CRYPTOPP_FILES "../cpp/*.cpp")
file(GLOB RN_CRYPTOPP_HEADERS "../cpp/*.h")
file(GLOB LIBRN_DIR "${BUILD_DIR}/react-native-0*/jni/${ANDROID_ABI}")

include_directories(
  ../cpp
  "${NODE_MODULES_DIR}/react-native/React"
  "${NODE_MODULES_DIR}/react-native/React/Base"
  "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
  "."

  # rncryptopp headers
  ${RN_CRYPTOPP_HEADERS}

  # Crypto++ headers
  ../cpp/android/${CMAKE_ANDROID_ARCH_ABI}/include

)


if (EXISTS "${LIBRN_DIR}/libjsi.so")
  # React Native 0.66.x and above

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
  # React Native 0.65.x and below
  set (JSI_LIB "")
  add_library(
          ${PACKAGE_NAME}
          SHARED
          "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp"
          ${RN_CRYPTOPP_FILES}
          ./cpp-adapter.cpp
  )
endif()

#Add JNI
 find_library(
         REACT_NATIVE_JNI_LIB
         reactnativejni
         PATHS ${LIBRN_DIR}
         NO_CMAKE_FIND_ROOT_PATH
 )

#Add LOG_LIB
find_library(
        LOG_LIB
        log
)

#Add cryptopp
add_library(cryptopp STATIC IMPORTED)

set_target_properties(
  # Target library
  cryptopp
  # Define property location
  PROPERTIES IMPORTED_LOCATION
  # Path to the library. Must be full path.
  ${PROJECT_SOURCE_DIR}/../cpp/android/${CMAKE_ANDROID_ARCH_ABI}/libcryptopp.a
)



target_link_libraries(
  ${PACKAGE_NAME}
  ${REACT_NATIVE_JNI_LIB}
  ${JSI_LIB}
  android
  cryptopp
  ${LOG_LIB}
)
