cmake_minimum_required(VERSION 3.21)



set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gpp.cmake)
set(BAREMETAL_DIR ${CMAKE_SOURCE_DIR}/baremetal)
set(APP_DIR ${CMAKE_SOURCE_DIR}/app)
set(HAL_DIR ${CMAKE_SOURCE_DIR}/hal/stm32f407xx)


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
add_library(hall_lib ${HAL_SOURCES})

# Specify the directory for the header files that are used for the project
include_directories(${HAL_DIR}/inc)

add_executable(${EXECUTABLE} 
    startup.c
    ${APP_DIR}/exp1_toggle_push_pull_led.cpp
)

# add_executable(${EXECUTABLE}
#         ${BAREMETAL_DIR}/startup.c
#         ${BAREMETAL_DIR}/main.c
#         ${BAREMETAL_DIR}/led.c
# )
# Link the library to the executable
target_link_libraries(${EXECUTABLE} hall_lib)

target_compile_options(${EXECUTABLE} PRIVATE
        -mcpu=${MACH}
        -mthumb
        -mfloat-abi=soft
        -Wall
        -fno-exceptions
        $<$<CONFIG:Debug>:-O0>
        )

target_link_options(${EXECUTABLE} PRIVATE
        -T ${CMAKE_SOURCE_DIR}/linker.ld
#        -nostdlib
        -mcpu=${MACH}
        -mthumb
        -mfloat-abi=soft
        --specs=nosys.specs
        -Wl,-Map=${PROJECT_NAME}.map
        )