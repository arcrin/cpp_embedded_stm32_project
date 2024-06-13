#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "resourceshell/macro_enum_map.h"

// #define EXPAND(x) x
// #define FOR_EACH_HELPER(macro, a1, ...) macro(a1) __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
// #define PRINT_INT(x) printf("%d\n", x);

#define OL 123          // Object-like macro
#define FL(x) ((x)+1)   // function-like macro

// enum EPOLL_EVENTS {
//     EPOLLIN = 0x001,
//     #define EPOLLIN EPOLLIN;
// }

#define LPAREN (
#define ID(arg) arg
#define ID2(arg) arg
#define ADD_ONE(arg) arg + 1

#define TO_STRING(x) #x
#define CONCATENATE(x, y) x ## y
#define MAKE_STRING_AND_CONCAT(x, y) TO_STRING(x ## y)

#define F_AGAIN() F
#define F() f F_AGAIN PARENS()

#define LOG(fmt, ...) printf(fmt __VA_OPT__(,) __VA_ARGS__);
#define LOG_DIGIT(digit) printf("%d\n", digit);

#define PARENS ()

// MAKE_ENUM(MyType, ZERO, ONE, TWO, THREE);
// void test(MyType e)
// {
//     std::cout << to_cstring(e) << " = " << e << std::endl;
// }

// MAKE_ENUM(Type1, T1_1, T1_2, T1_3);

int main(int, char**){
    // char cstr1cstr2[] = "Hello World!"; 
    // uint8_t var1 = 42;
    // uint8_t var2 = 100;
    // printf("%s\n", TO_STRING(Hello));
    // printf("%d\n", CONCATENATE(var, 1));
    // printf("%d\n", CONCATENATE(var, 2));
    // printf("%s\n", MAKE_STRING_AND_CONCAT(Hello, World!));
    // printf("%d\n", ID()ID(5));
    // printf("%d\n", ID(ID2(ID)(5)));
    // FOR_EACH(LOG_DIGIT, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    // test(ZERO);
    // test(ONE);
    // test(TWO);
    // test(THREE);
    // printf("%d", ADD_ONE(ADD_ONE(1)));
    FOR_EACH(LOG_DIGIT, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
}
