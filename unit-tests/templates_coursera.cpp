#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>


template <typename Collection>
std::string Join(const Collection& c, char d) {
    std::stringstream ss;
    bool first = true;
    for (const auto& i : c) {
        if (!first) {
            ss << d;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template <typename First, typename Second>
std::ostream& operator<< (std::ostream& out, const std::pair<First, Second>& p) {
    return out <<  '(' << p.first << ',' << p.second << ')';
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& vi) {
    return out << '[' << Join(vi, ',') << ']';
}

template <typename Key, typename Value>
std::ostream& operator<< (std::ostream& out, const std::map<Key, Value>& mi) {
    return out << '{' << Join(mi, ' ') << '}'; 
}

int main() {

    std::vector<double> vi {1.3, 2, 4};
    std::cout << vi << std::endl;
    std::map<int, int> m {{1, 2}, {3, 4}};
    std::cout << m << " " << std::endl; 

    return 0;
}
