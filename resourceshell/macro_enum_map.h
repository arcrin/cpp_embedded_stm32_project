#pragma once

#define PARENS()
#define EXPAND1(...) __VA_ARGS__
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS))))
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))

#define FOR_EACH_AGAIN() FOR_EACH_HELPER
#define FOR_EACH_HELPER(macro, a1, ...) macro(a1) __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH(macro, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))

// #define ENUM_CASE(name)             \
//     case name:                      \
//         return #name;

// #define MAKE_ENUM(type, ...)                            \
//     enum type {__VA_ARGS__};                            \
//     constexpr const char * to_cstring(type _e)          \
//     {                                                   \
//         using enum type;                                \
//         switch (_e){                                    \
//         FOR_EACH(ENUM_CASE, __VA_ARGS__)                \
//         default: return "unknown";                      \
//         }                                               \
//     }

#define MAKE_ENUM(type_name, ...)   \
type_name{                          \
    __VA_ARGS__                     \
}

#define MAKE_MAP(type_name, ...)    \
type_name{                          \
    __VA_ARGS__                     \
}

#define KEY_HELPER(key, ...) key,
#define NAME_ONLY_HELPER(key, ...) {#key},
#define BRACED_INIT_LIST(...) {__VA_ARGS__}
#define NAMED_BRACED_VALUE_HELPER(key, A) {#key, BRACED_INIT_LIST A},
#define NAMED_VALUE_HELPER(key, ...) {#key, {__VA_ARGS__}},
#define UNNAMED_VALUE_HELPER(key, ...) {__VA_ARGS__},

#define FOR_EACH_HELPER_NONE(macro, a1, ...) macro(a1) __VA_OPT__(FOR_EACH_AGAIN_NONE PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_1(macro, a1, a2, ...) macro(a1, a2) __VA_OPT__(FOR_EACH_AGAIN_1 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_2(macro, a1, a2, a3, ...) macro(a1, a2, a3) __VA_OPT__(FOR_EACH_AGAIN_2 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_3(macro, a1, a2, a3, a4, ...) macro(a1, a2, a3, a4) __VA_OPT__(FOR_EACH_AGAIN_3 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_4(macro, a1, a2, a3, a4, a5, ...) macro(a1, a2, a3, a4, a5) __VA_OPT__(FOR_EACH_AGAIN_4 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_5(macro, a1, a2, a3, a4, a5, a6, ...) macro(a1, a2, a3, a4, a5, a6) __VA_OPT__(FOR_EACH_AGAIN_5 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_6(macro, a1, a2, a3, a4, a5, a6, a7, ...) macro(a1, a2, a3, a4, a5, a6, a7) __VA_OPT__(FOR_EACH_AGAIN_6 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_7(macro, a1, a2, a3, a4, a5, a6, a7, a8, ...) macro(a1, a2, a3, a4, a5, a6, a7, a8) __VA_OPT__(FOR_EACH_AGAIN_7 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_8(macro, a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) macro(a1, a2, a3, a4, a5, a6, a7, a8, a9) __VA_OPT__(FOR_EACH_AGAIN_8 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_HELPER_9(macro, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) macro(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) __VA_OPT__(FOR_EACH_AGAIN_9 PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN_NONE() FOR_EACH_HELPER_NONE
#define FOR_EACH_AGAIN1() FOR_EACH_HELPER_1
#define FOR_EACH_AGAIN2() FOR_EACH_HELPER_2 
#define FOR_EACH_AGAIN3() FOR_EACH_HELPER_3
#define FOR_EACH_AGAIN4() FOR_EACH_HELPER_4 
#define FOR_EACH_AGAIN5() FOR_EACH_HELPER_5
#define FOR_EACH_AGAIN6() FOR_EACH_HELPER_6
#define FOR_EACH_AGAIN7() FOR_EACH_HELPER_7
#define FOR_EACH_AGAIN8() FOR_EACH_HELPER_8
#define FOR_EACH_AGAIN9() FOR_EACH_HELPER_9