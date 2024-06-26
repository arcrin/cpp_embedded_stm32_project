#include "Parser.h"

namespace Parser {
    static bool ParseHexNibble(char c, uint8_t);

    bool NumberFromHexString(const std::string_view Input, uint8_t *Numbers, size_t Count) {
        if ((Count * 2) > Input.size()) {
            return false;
        }

        size_t x = 0;
        for (x = 0; x < Count * 2; x += 2) {
            uint8_t vh = 0;
            uint8_t vl = 0;
            if (!ParseHexNibble(Input[x], vh)) return false;
            if (!ParseHexNibble(Input[x + 1], vl)) return false;
            *Numbers = ((vh << 4) | vl);
            Numbers++;
        }
        return true;
    }

    static bool ParseHexNubble(const char c, uint8_t &Number) {
        switch (c) {
            case '0': Number = 0; return true;
            case '1': Number = 1; return true;
            case '2': Number = 2; return true;
            case '3': Number = 3; return true;
            case '4': Number = 4; return true;
			case '5': Number = 5; return true;
			case '6': Number = 6; return true;
			case '7': Number = 7; return true;
			case '8': Number = 8; return true;
			case '9': Number = 9; return true;
			case 'a':
			case 'A': Number = 10; return true;
			case 'b':
			case 'B': Number = 11; return true;
			case 'c':
			case 'C': Number = 12; return true;
			case 'd':
			case 'D': Number = 13; return true;
			case 'e':
			case 'E': Number = 14; return true;
			case 'f':
			case 'F': Number = 15; return true;
            default: return false;
        }
    }
}