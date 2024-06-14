#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "resourceshell/macro_enum_map.h"
#include "resourceshell/ShellErr.h"


// #define ID(arg) arg
// #define ID2(arg) arg
// #define ADD_ONE(arg) arg + 1

// #define TO_STRING(x) #x
// #define CONCATENATE(x, y) x ## y
// #define MAKE_STRING_AND_CONCAT(x, y) TO_STRING(x ## y)

// #define LOG(fmt, ...) printf(fmt __VA_OPT__(,) __VA_ARGS__);
#define LOG_DIGIT(digit) printf("%d\n", digit);
#define LOG_2DIGIT(digit1, digit2) printf("%d %d\n", digit1, digit2);
#define LOG_3DIGIT(digit1, digit2, digit3) printf("%d %d %d\n", digit1, digit2, digit3);

// #define PARENS ()

// #define F(a1, ...) f##a1  __VA_OPT__(F_AGAIN PARENS (__VA_ARGS__))
// #define F_AGAIN() F

// #define EXPAND1(...) __VA_ARGS__
// #define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
// #define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
// #define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
// #define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))

// #define FOR_EACH_AGAIN() FOR_EACH_HELPER
// #define FOR_EACH_HELPER(macro, a1, ...) macro(a1) __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
// #define FOR_EACH(macro, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))

// enum class SHELLERR : uint8_t{ 
//     OK, 
//     IMPLEMENTATION,
//     EXECUTION, 
//     RESOURCE, 
//     ARGUMENT, 
//     CHECKSUM, }; 
// constexpr std::string_view SHELLERRStrings[]{ 
//     "", 
//     "IMPLEMENTATION - NOT IMPLEMENTED", 
//     "EXECUTION - COMMAND FAILED", 
//     "RESOURCE - NO SUCH RESOURCE", 
//     "ARGUMENT - BAD ARGUMENT", 
//     "CHECKSUM - COMMAND/RESOURCE CHECKSUM FAILURE", };

int main(int, char**){
    SHELLERR error = SHELLERR::EXECUTION;
    std::cout << "Error: " << SHELLERRStrings[static_cast<uint8_t>(error)] << std::endl;
    return 0;
}
