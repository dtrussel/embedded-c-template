#!/usr/bin/env bash
set -e

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

BUILD_DIR=${SCRIPT_DIR}/build
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# native build
mkdir -p clang-native
cd clang-native
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/clang-native.cmake ../..
ninja

# run unit tests
export LLVM_PROFILE_FILE="mbed-tests.profraw"
MERGED_PROFILE_DATA="mbed.profdata"
IGNORE_FILES_OPTIONS=--ignore-filename-regex='.*_deps\/.*|.*test\/.*' # ignore all files from dependencies and unit tests files
./mbed-tests
llvm-profdata merge -sparse ${LLVM_PROFILE_FILE} -o ${MERGED_PROFILE_DATA}
llvm-cov show ./mbed-tests --instr-profile=${MERGED_PROFILE_DATA} --format=html --output-dir=${BUILD_DIR}/coverage-report ${IGNORE_FILES_OPTIONS}
llvm-cov report ./mbed-tests --instr-profile=${MERGED_PROFILE_DATA} ${IGNORE_FILES_OPTIONS}
cd ..
tar czf coverage-report.tar.gz ${BUILD_DIR}/coverage-report

# target build
mkdir -p gcc-arm-none-eabi
cd gcc-arm-none-eabi
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/gcc-arm-none-eabi.cmake \
  -D MBED_DISABLE_TESTS=1 ../..
ninja
