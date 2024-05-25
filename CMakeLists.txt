cmake_minimum_required(VERSION 3.15.0)



set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gpp.cmake)
set(BAREMETAL_DIR ${CMAKE_SOURCE_DIR}/baremetal)
project(cpp_stm32_embedded)

enable_language(C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -std=gnu11 -Wall -O0")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -T ${CMAKE_SOURCE_DIR}/linker.ld -Wl,-Map=${PROJECT_NAME}.map")

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_executable(${EXECUTABLE} 
    ${BAREMETAL_DIR}/main.c
    ${BAREMETAL_DIR}/led.c
    ${BAREMETAL_DIR}/startup.c
)