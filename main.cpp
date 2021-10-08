
#include <iostream>
#include <vector>
#include <cstring>

#include "rpn.h"
using namespace std;

int main(int argc, char* argv[]) {

    bool is_print_needed = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            is_print_needed = true;
        }
    }


    string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};
    int n = 9;

    double result = rpn(test, n, is_print_needed);
    cout << result << endl;

    return 0;
}