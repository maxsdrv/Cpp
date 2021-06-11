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
    return synonyms[first_word].count(second_word) == 0; 
}                   

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "(";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << kv.second;
    }
    return os;
}

void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

void TestAddSynonyms() {
    {
        map empty;
        AddSynonyms(empty, "a", "b");
        const map expected = {
            {"a", {"b"}},
            {"b", {"a"}},
        };
        AssertEqual(empty, expected, "Add to empty");
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
        AssertEqual(synonyms, expected, "Add to non-empty");
    }
    std::cout << "TestAddSynonyms OK" << std::endl;
}

void TestCount() {
    {
        map empty;
        AssertEqual(GetCount(empty, "a"), 0u, "count for empty");
    }
    {
        map synonyms = {
            {"a", {"b", "c"}}, 
            {"b", {"a"}},
            {"c", {"a"}}
        };
        AssertEqual(GetCount(synonyms, "a"), 2u, "count for a");
        AssertEqual(GetCount(synonyms, "b"), 1u, "count for b");
        AssertEqual(GetCount(synonyms, "z"), 0u, "count for z");
    }
    std::cout << "TestCount OK" << std::endl;
}

void TestAreSynonyms() {
    {   map empty;
        Assert(!CheckSynonyms(empty, "a", "b"), "empty a b");
        Assert(!CheckSynonyms(empty, "b", "a"), "empty b a");
    }
    {
        map synonyms = {
            {"a", {"b", "c"}}, 
            {"b", {"a"}}, 
            {"c", {"a"}}
        };
        Assert(CheckSynonyms(synonyms, "a", "b"), "");
        Assert(CheckSynonyms(synonyms, "b", "a"), "");
        Assert(CheckSynonyms(synonyms, "a", "c"), "");
        Assert(CheckSynonyms(synonyms, "c", "a"), "");
        Assert(!CheckSynonyms(synonyms, "c", "b"), "");
        Assert(!CheckSynonyms(synonyms, "b", "c"), "");
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