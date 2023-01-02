set(CMAKE_ASM_COMPILER clang)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(COVERAGE_GEN_FLAGS "-fprofile-instr-generate -fcoverage-mapping")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${COVERAGE_GEN_FLAGS} ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_GEN_FLAGS} ")
