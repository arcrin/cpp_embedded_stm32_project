cmake_minimum_required(VERSION 3.21)

set(CMAKE_COLOR_MAKEFILE OFF)

# Set this variable to match the MCU you are working with. 
# At this point, it needs to match the dir name where the HAL is defined.
set(MCU_TYPE stm32f407xx)
# set(MCU_TYPE stm32f103xx)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gpp.cmake)
set(BAREMETAL_DIR ${CMAKE_SOURCE_DIR}/baremetal)
set(APP_DIR ${CMAKE_SOURCE_DIR}/app)
set(HAL_DIR ${CMAKE_SOURCE_DIR}/hal/${MCU_TYPE})


project(cpp_stm32_embedded)

enable_language(C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(MACH cortex-m4)

# set(CMAKE_C_FLAGS "-mcpu=${MACH} -mthumb -mfloat-abi=soft -Wall -fno-exceptions -O0")
# set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -T ${CMAKE_SOURCE_DIR}/linker.ld -mcpu=${MACH} -mthumb -mfloat-abi=soft --specs=nosys.specs -Wl,-Map=${PROJECT_NAME}.map")

set(EXECUTABLE ${PROJECT_NAME}.elf)

# Create a library from the source files in HAL_DIR
file(GLOB HAL_SOURCES ${HAL_DIR}/src/*.cpp)
message(STATUS "All source files ${HAL_SOURCES}" )
message(STATUS "Build Configuration: ${CMAKE_BUILD_TYPE}")

# Specify the directory for the header files that are used for the project
include_directories(${HAL_DIR}/inc)
include_directories(${APP_DIR}/${MCU_TYPE})

add_executable(${EXECUTABLE} 
    ${HAL_DIR}/startup.c
    ${HAL_SOURCES}
    ${APP_DIR}/${MCU_TYPE}/main.cpp
)

target_compile_options(${EXECUTABLE} PRIVATE
        -mcpu=${MACH}
        -mthumb
        -mfloat-abi=soft
        -Wall
        -fno-exceptions
        # $<$<CONFIG:Debug>:-O0>
        -O0
        )

target_link_options(${EXECUTABLE} PRIVATE
        -T ${HAL_DIR}/linker.ld
        # -nostdlib
        -mcpu=${MACH}
        -mthumb
        -mfloat-abi=soft
        --specs=nosys.specs
        -Wl,-Map=${PROJECT_NAME}.map
        )
get_target_property(EXECUTABLE_COMPILE_OPTIONS ${EXECUTABLE} COMPILE_OPTIONS)
message(STATUS "Compile options for ${EXECUTABLE}: ${EXECUTABLE_COMPILE_OPTIONS}")

get_target_property(EXECUTABLE_LINK_OPTIONS ${EXECUTABLE} LINK_OPTIONS)
message(STATUS "Link options for ${EXECUTABLE}: ${EXECUTABLE_LINK_OPTIONS}")

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} $<TARGET_FILE:${EXECUTABLE}>
        COMMENT "Printing size of the executable ${EXECUTABLE}"
        COMMAND arm-none-eabi-objdump -S -C ${PROJECT_NAME}.elf > ${PROJECT_NAME}.lst
)

