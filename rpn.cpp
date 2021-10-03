
#include "rpn.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/******** handler function ******/
double rpn(vector<string> strs) {
    RPN* model = new RPN(strs);
    return model->calculate();
}

/******** helper functions *****/

/**
 * @brief check if a string is a number
 * 
 * @param str the string to check
 * @return true if string is numeric
 * @return false otherwise
 */
bool is_number(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief check if a string is am operator
 * 
 * @param str the string to check
 * @return true if string is operator
 * @return false otherwise
 */
bool is_operator(string str) {
    return str == "+" ||
           str == "-" ||
           str == "*" ||
           str == "/" ||
           str == "<" ||
           str == ">" ||
           str == "**";
}

/******** RPN Model Class ******/
RPN::RPN(vector<string>& strs) {
    // base case
    if (strs.empty()) {
        return;
    }
    this->value = strs.back();
    strs.pop_back();

    if (is_number(this->value)) {
        return;
    }

    this->right = new RPN(strs);
    this->left = new RPN(strs);
}

double RPN::calculate() {
    double result = 0.0;

    if (this->isLeaf()) {
        return atof(this->value.c_str());
    }

    double a = this->left->calculate();
    double b = this->right->calculate();

    if (this->value == "+") {
        result = a + b;
    } else if (this->value == "-") {
        result = a - b;
    } else if (this->value == "-") {
        result = a - b;
    } else if (this->value == "*") {
        result = a * b;
    } else if (this->value == "/") {
        result = a / b;
    } else if (this->value == "**") {
        result = pow(a, b);
    } else {
		throw "Invalid Operation";
	}

    return result;
}

void RPN::print() {
    cout << this->value << endl;
    if (this->isLeaf()) {
        return;
    }

    this->left->print();
    this->right->print();
}

bool RPN::isLeaf() {
    return is_number(this->value) && !this->left && !this->right;
}

bool RPN::isLastTree() {
    return is_operator(this->value) &&
           this->left->isLeaf() && this->right->isLeaf();
}
