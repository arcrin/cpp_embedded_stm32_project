#pragma once
#include <algorithm>
#include <string_view>
#include <strings.h>
#include <cstring>


class Searchable {
    public:
        constexpr Searchable(std::string_view Name) : SearchableName(Name) {}
        [[nodiscard]] inline constexpr std::string_view GetName() const {return SearchableName;}

        #define SEARCH_PARTIAL_UNIQUE(Map, Term) Searchable::SearchPartialUnique(Map, sizeof(Map) / sizeof(Map[0]), Term)

        template <typename T>
        static constexpr int32_t SearchPartialUnique(const T *Map, uint32_t Length, std::string_view Term) {
            static_assert(std::is_base_of_v<Searchable, T>);
            return SearchPartialUnique_impl((void *) Map, sizeof(T), Length, Term);
        }

    
    private:
        const std::string_view SearchableName;


        static constexpr uint32_t SearchPartialUnique_impl(const void *Map, uint32_t Size, int32_t Length, std::string_view Term) {
            int32_t Index = -1;

            for (int32_t candidate_idx = 0; candidate_idx < Length; candidate_idx++) {
                const auto &Candidate = ((Searchable*)&((uint8_t*)Map)[candidate_idx * Size]) -> GetName(); 
                uint32_t SearchLoops = (uint32_t) std::max(0L, 1L + (int)Candidate.size() - (int)Term.size());
                for (uint32_t candidate_offset = 0; candidate_offset < SearchLoops; candidate_offset++) {
                    if(!strncasecmp(&Candidate[candidate_offset], Term.data(), Term.size())) {
                        if(Candidate.size() == Term.size()) {
                            return candidate_idx;
                        }
                        if(Index >= 0 && Index != candidate_idx) {
                            return -1;
                        }
                        Index = candidate_idx;
                    }
                }
            }
            return Index;
        }
};

template <typename T>
class SearchableRef : public Searchable {
    public:
        constexpr SearchableRef(std::string_view Name, T& Resource) : Searchable(Name), Resource(std::move(Resource)) {}
        inline constexpr T& get() const {return Resource;}
        inline constexpr const T& getconst() const {return Resource;}

    private:
        const T& Resource;
};

template <typename T>
class SearchableVal : public Searchable {
    public:
        constexpr SearchableVal(std::string_view Name, T Resource) : Searchable(Name), Resource(std::move(Resource)) {}
        inline constexpr T& getref() {return Resource;} 
        inline constexpr const T& getconstref() const {return Resource;}    
    private:
        T Resource;
};