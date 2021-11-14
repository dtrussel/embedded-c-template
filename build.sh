#!/usr/bin/env bash
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

BUILD_DIR=${SCRIPT_DIR}/build
rm -rf ${BUILD_DIR} || true
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

mkdir -p clang
cd clang
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/clang.cmake ../..
ninja
./mbed-tests

cd ..
mkdir clang-arm-none-eabi
cd clang-arm-none-eabi
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/gcc-arm-none-eabi.cmake \
  -D MBED_DISABLE_UNIT_TESTS=1 ../..
ninja
