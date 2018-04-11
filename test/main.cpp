#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {

    string text = "this. is my string. it's here.";
    string result;

    std::remove_copy_if(text.begin(), text.end(),
                        std::back_inserter(result), //Store output
                        std::ptr_fun<int, int>(&std::ispunct)
    );
    cout << result << endl;
    return 0;
}