cmake_minimum_required(VERSION 3.15.0)

project(cpp_stm32_embedded)

enable_language(C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gpp.cmake)