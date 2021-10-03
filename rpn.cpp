
#include "rpn.h"

#include <iostream>
#include <vector>
using namespace std;

/******** handler function ******/
double rpn(vector<string> strs) {
    RPN model = RPN(strs);
    return model.calculate();
}

/******** RPN Model Class ******/
RPN::RPN(vector<string> strs) {
}

double RPN::calculate() {
    double result = 0.0;

    // Calculate the result here
    // You may add extra functions if needed

    return result;
}
