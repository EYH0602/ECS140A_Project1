
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

/******** RPN Model Class ******/

RPN::RPN(vector<string>& strs) {
    // base case
    if (strs.empty()) {
        return;
    }
    this->value = strs.back();
    strs.pop_back();

    if (this->is_number()) {
        return;
    }

    if (this->is_unary_op()) {
        this->next = new RPN(strs);
    } else {
        this->right = new RPN(strs);
        this->left = new RPN(strs);
    }
}

double RPN::calculate() {
    double result = 0.0;

    if (this->isLeaf()) {
        return atof(this->value.c_str());
    }

    if (this->is_unary_op()) {
        double num = this->next->calculate();
		cout << "rounding " << num << endl;
        if (this->value == "<") {
            result = floor(num);
        } else if (this->value == ">") {
            result = ceil(num);
        } else {
            throw "Invalid Operation";
        }
        return result;
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

	if (this->is_unary_op()) {
		this->next->print();
	} else {
		this->left->print();
		this->right->print();
	}

}

bool RPN::isLeaf() {
    return (this->is_number() && !this->left && !this->right) ||
           (this->is_number() && !this->next);
}

bool RPN::isLastTree() {
    return this->is_binary_op() &&
           this->left->isLeaf() && this->right->isLeaf();
}


/**
 * @brief check if a string is a number
 * 
 * @param str the string to check
 * @return true if string is numeric
 * @return false otherwise
 */
bool RPN::is_number() {
    for (char c : this->value) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief check if a string is an binary operator
 * 
 * @param str the string to check
 * @return true if string is operator
 * @return false otherwise
 */
bool RPN::is_binary_op() {
    string str = this->value;
    return str == "+" ||
           str == "-" ||
           str == "*" ||
           str == "/" ||
           str == "<" ||
           str == ">" ||
           str == "**";
}

/**
 * @brief check if a string is an singleton operator
 * 
 * @param str the string to check
 * @return true if string is operator
 * @return false otherwise
 */
bool RPN::is_unary_op() {
    return this->value == "<" || this->value == ">";
}
