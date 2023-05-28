set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(OBJECT_GEN_FLAGS "-O0 -fno-builtin -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -mthumb")

set(CMAKE_C_FLAGS   "${OBJECT_GEN_FLAGS} ")
set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} ")
set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS} -x assembler-with-cpp ")
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=ldd-16")

set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_ASM_FLAGS_DEBUG "-g")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_C_FLAGS_RELEASE "-Oz -flto")
set(CMAKE_CXX_FLAGS_RELEASE "-Oz -flto")
set(CMAKE_ASM_FLAGS_RELEASE "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto")

set(CMAKE_C_COMPILER_TARGET armv7em-none-eabi)
set(CMKAE_CXX_COMPILER_TARGET armv7em-none-eabi)

set(CMAKE_ASM_COMPILER clang-16)
set(CMAKE_C_COMPILER clang-16)
set(CMAKE_CXX_COMPILER clang++-16)
set(CMAKE_AR llvm-ar-16)
set(CMAKE_NM llvm-nm-16)
set(CMAKE_LINKER lld-16)
set(CMAKE_RANLIB llvm-ranlib-16)

set(CMAKE_SYSROOT /usr/arm-none-eabi)

set(MBED_WARNINGS_FLAGS -Wall -Wextra -pedantic -Werror)
