#!/usr/bin/env bash
set -e

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

BUILD_DIR=${SCRIPT_DIR}/build
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

mkdir -p clang-native
cd clang-native
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/clang-native.cmake ../..
ninja
./mbed-tests

cd ..
mkdir -p gcc-arm-none-eabi
cd gcc-arm-none-eabi
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/gcc-arm-none-eabi.cmake \
  -D MBED_DISABLE_TESTS=1 ../..
ninja
