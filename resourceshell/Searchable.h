#pragma once
#include <algorithm>
#include <string_view>
#include <cstring>

class Searchable{
    public:
        // not marked explicit so that it is implicitly convertible from a const char*
        constexpr Searchable(std::string_view Name) : SearchableName(Name) {}
        [[nodiscard]] inline constexpr std::string_view GetName() const {return SearchableName;}

    private:
        const std::string_view SearchableName;

        // This was broken into a separate function so that the templated part above is as small as possible
        static constexpr uint32_t SearchPartialUnique_impl(const void *Map, uint32_t Size, int32_t Length, std::string_view Term) {
            int32_t Index = -1;

            // Loop through each item in the map
            for (int32_t candidate_idx = 0; candidate_idx < Length; candidate_idx++) {
                // If the term is shorter than the candidate, search for the term multiple times at increasing offset
                // from the first character of the candidate
                const auto &Candidate = ((Searchable*)&((uint8_t*)Map))
            }
        }
};