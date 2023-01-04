set(CMAKE_ASM_COMPILER clang)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(MBED_COVERAGE_FLAGS -fprofile-instr-generate -fcoverage-mapping)
set(MBED_WARNINGS_FLAGS -Wall -Wextra -pedantic -Werror)
