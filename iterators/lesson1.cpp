#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>


using namespace std;

struct Lang {
    string name;
    int age;
};

int main() {

    vector<Lang> langs =  {{"Python", 22}};
    auto result = find_if (begin(langs), end(langs), [](const Lang& lang){
        return lang.name[0] == 'C';  
    });
    // string& ref = *result;
    // ref = "D++";
    // cout << *result << endl;
    // *result = "C++";
    // cout << *result << endl;
    cout << result->age << endl;


	return 0;
}