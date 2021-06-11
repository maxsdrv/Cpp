#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include <sstream>
#include <exception>



using map = std::map<std::string, std::set<std::string>>;

void AddSynonyms(map& synonyms, const std::string& first_word, 
                const std::string& second_word) {
    synonyms[first_word].insert(second_word);
    synonyms[second_word].insert(first_word);
}

size_t GetCount(map& synonyms, const std::string& word) {
    return synonyms[word].size();
}

bool CheckSynonyms(map& synonyms, const std::string& first_word, 
                   const std::string& second_word) {
    return synonyms[first_word].count(second_word) == 1; 
}                   

template <typename T, typename U>
void AssertEqual(const T& t, const U& u) {
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        throw std::runtime_error(os.str());
    }
}

void TestAddSynonyms() {
    {
        map empty;
        AddSynonyms(empty, "a", "b");
        const map expected = {
            {"a", {"b"}},
            {"b", {"a"}},
        };
        assert (empty == expected);
    }
    {
        map synonyms = {
            {"a", {"b"}},
            {"b", {"a", "c"}},
            {"c", {"b"}}
        };
        AddSynonyms(synonyms, "a", "c");
        const map expected = {
            {"a", {"b", "c"}},
            {"b", {"a", "c"}},
            {"c", {"b", "a"}}
        };
        assert (synonyms == expected);
    }
    std::cout << "TestAddSynonyms OK" << std::endl;
}

void TestCount() {
    {
        map empty;
        assert(GetCount(empty, "a") == 0);
    }
    {
        map synonyms = {
            {"a", {"b", "c"}}, 
            {"b", {"a"}},
            {"c", {"a"}}
        };
        AssertEqual(GetCount(synonyms, "a"), 2);
        AssertEqual(GetCount(synonyms, "b"), 1);
        AssertEqual(GetCount(synonyms, "z"), 0);
    }
    std::cout << "TestCount OK" << std::endl;
}

void TestAreSynonyms() {
    {   map empty;
        assert(!CheckSynonyms(empty, "a", "b"));
        assert(!CheckSynonyms(empty, "b", "a"));
    }
    {
        map synonyms = {
            {"a", {"b", "c"}}, 
            {"b", {"a"}}, 
            {"c", {"a"}}
        };
        assert(CheckSynonyms(synonyms, "a", "b"));
        assert(CheckSynonyms(synonyms, "b", "a"));
        assert(CheckSynonyms(synonyms, "a", "c"));
        assert(CheckSynonyms(synonyms, "c", "a"));
        assert(!CheckSynonyms(synonyms, "c", "b"));
        assert(!CheckSynonyms(synonyms, "b", "c"));
    }
    std::cout << "TestAreSynonyms OK" << std::endl;
}

void TestAll() {
    TestCount();
    TestAreSynonyms();
    TestAddSynonyms();
}

int main() {
    TestAll();
    return 0;
    
    int q = 0;
    std::cin >> q;

    map synonyms;
    

    for(int i = 0; i < q; ++i) {
        std::string operation_code;
        std::cin >> operation_code;

        if (operation_code == "ADD") {
            std::string first_word, second_word;
            std::cin >> first_word >> second_word;
            AddSynonyms(synonyms, first_word, second_word); 
        }
        else if (operation_code == "COUNT") {
            std::string word;
            std::cin >> word;
            GetCount(synonyms, word);
        }
        else if (operation_code == "CHECK") {
            std::string first_word, second_word;
            std::cin >> first_word >> second_word;
            if (CheckSynonyms(synonyms, first_word, second_word)) {
                std::cout << "YES" << std::endl;
            }
            else {
                std::cout << "NO" << std::endl;
            }
        }
    } 
    




	return 0;
}