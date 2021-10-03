
#include <iostream>
#include <vector>

#include "rpn.h"
using namespace std;

int main() {
    vector<string> test = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};

    double result = rpn(test);
    cout << result << endl;
}