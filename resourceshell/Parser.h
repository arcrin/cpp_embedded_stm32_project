#pragma once
#include "resource_shell_config.h"
#include <cstdint>
#include <string_view>
#include "boost/static_string.hpp"

namespace Parser {
    bool NumbersFromHexString(std::string_view Input, uint8_t *Numbers, size_t Count);

    void HexStringFromNumbers(const void* Numbers, uint32_t Count, boost::static_string<RESOURCE_SHELL_OUTPUT_SIZE> &Output, bool Reverse=false);

    template <typename T>
    void HexFromNumber(T Number, boost::static_string <RESOURCE_SHELL_OUTPUT_SIZE> &Output) {
        HexStringFromNumbers((uint8_t*)&Number, sizeof(T), Output, true);
    }

    bool InternalnumberFromString(std::string_view Input, int32_t &Number);

    template <typename T>
    bool NumberFromString(const std::string_view Input, T &Number) {
        int32_t val;
        bool res = InternalNumberFromString(Input, val);
        Number = (T)val;
        return res;
    }
}