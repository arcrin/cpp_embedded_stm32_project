#include <iostream>
#include <stdio.h>
#include <stdint.h>

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
#define ADD(a, b) a + b

#define TO_STRING(x) #x
#define CONCATENATE(x, y) x ## y
#define MAKE_STRING_AND_CONCAT(x, y) TO_STRING(x ## y)



int main(int, char**){
    char cstr1cstr2[] = "Hello World!"; 
        
    uint8_t var1 = 42;
    uint8_t var2 = 100;
    printf("%s\n", TO_STRING(Hello));
    printf("%d\n", CONCATENATE(var, 1));
    printf("%d\n", CONCATENATE(var, 2));
    printf("%s\n", MAKE_STRING_AND_CONCAT(Hello, World!));
    printf("%d\n", ID()ID(5));
    
    return 0;
}
