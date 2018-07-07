cmake_minimum_required(VERSION 3.9)
project(kernel)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
enable_language(ASM_NASM)

set(CMAKE_C_FLAGS "${ISA_C_FLAGS} ${PLATFORM_C_FLAGS} -Os -fno-strict-aliasing -fstack-protector -m32 ${SIMD_OPTIONS} ${ARCH_OPTIONS} -Wwrite-strings -ffast-math ${SANITIZER_OPTIONS} -std=c11 -Wall -Wextra -Wconversion -Wcast-qual -Wno-unused-parameter -Wno-implicit-int -Wnull-dereference -lgcc -static-libgcc -ffreestanding -fno-builtin -nostdlib -fno-omit-frame-pointer -Werror=implicit-function-declaration -lgcc")
set(CMAKE_CXX_FLAGS "${ISA_CXX_FLAGS} ${PLATFORM_CXX_FLAGS} -Os -fno-exceptions -fno-strict-aliasing -m32 ${SIMD_OPTIONS} ${ARCH_OPTIONS} -Wwrite-strings -Wsuggest-final-types -Wsuggest-final-methods -Wconversion -Woverloaded-virtual -ffast-math ${SANITIZER_OPTIONS} -fstack-protector -std=c++17 -Wall -Wextra -Wlogical-op -Wno-cast-qual -Wdouble-promotion -Wno-unused-parameter -Wno-format -Wno-switch -Wno-packed-bitfield-compat -Wno-reorder -Wno-trigraphs -lgcc -static-libgcc -ffreestanding -fno-builtin -nostdlib -fno-omit-frame-pointer -Werror=implicit-function-declaration -lgcc")

set(SOURCES
        src/kernel.asm
        src/kmain.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/src/kernel.ld)
set(CMAKE_EXE_LINKER_FLAGS "-N -T${LINKER_SCRIPT}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".bin")


# test os >>qemu-system-i386 -kernel kernel.bin