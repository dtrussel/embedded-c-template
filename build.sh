#!/usr/bin/env bash
set -e

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

BUILD_DIR=${SCRIPT_DIR}/build
BUILD_DIR_NATIVE=${BUILD_DIR}/clang-native
BUILD_DIR_TARGET=${BUILD_DIR}/gcc-arm-none-eabi

# native build
mkdir -p ${BUILD_DIR_NATIVE}
cd ${BUILD_DIR_NATIVE}
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/clang-native.cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=1 ${SCRIPT_DIR}
ninja

# run unit tests
export LLVM_PROFILE_FILE="${BUILD_DIR_NATIVE}/mbed-tests.profraw"
MERGED_PROFILE_DATA="${BUILD_DIR_NATIVE}/mbed.profdata"
IGNORE_FILES_OPTIONS=--ignore-filename-regex='.*_deps\/.*|.*test\/.*' # ignore all files from dependencies and unit tests files
./mbed-tests
llvm-profdata merge -sparse ${LLVM_PROFILE_FILE} -o ${MERGED_PROFILE_DATA}
llvm-cov show ./mbed-tests --instr-profile=${MERGED_PROFILE_DATA} --format=html --output-dir=${BUILD_DIR}/coverage-report ${IGNORE_FILES_OPTIONS}
llvm-cov report ./mbed-tests --instr-profile=${MERGED_PROFILE_DATA} ${IGNORE_FILES_OPTIONS}

# target build
mkdir -p ${BUILD_DIR_TARGET}
cd ${BUILD_DIR_TARGET}
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=${SCRIPT_DIR}/toolchain/gcc-arm-none-eabi.cmake \
  -D MBED_DISABLE_TESTS=1 ${SCRIPT_DIR}
ninja

cd ${SCRIPT_DIR}
