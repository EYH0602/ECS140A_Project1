
#include <iostream>
#include <vector>

#include "rpn.h"
using namespace std;

int main() {
    string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};
    int n = 9;

    double result = rpn(test, n);
    cout << result << endl;

    return 0;
}