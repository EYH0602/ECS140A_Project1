
#include "rpn.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/******** handler function ******/
double rpn(string* strs, int n, bool is_print_needed) {
    vector<string> elements;
    for (int i = 0; i < n; i++) {
        elements.push_back(strs[i]);
    }
    RPN* model = new RPN(elements);
    if (is_print_needed) {
        model->print();
    }
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
        this->right = new RPN(strs);
    } else {
        this->right = new RPN(strs);
        this->left = new RPN(strs);
    }
}

double RPN::calculate() {
    double result = 0.0;

    if (this->is_leaf()) {
        return stof(this->value.c_str());
    }

    if (this->is_unary_op()) {
        double num = this->right->calculate();
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

/**
 * @brief print the parse tree as required in project1.pdf part 2
 * 
 */
void RPN::print() {
    // start printing the tree at the root
    this->print(0);
}

/**
 * @brief helper function of print,
 * indent the line according to depth.
 * NOTE: two space indentation
 * 
 * @param depth the level of the node, the root starts with 0 
 */
void RPN::indent(int depth) {
    for (int i = 0; i < depth; i++) {
        cout << "  ";  // two space indentation
    }
}

/**
 * @brief helper function of print,
 * start printing at depth
 * 
 * @param depth the level of the node, the root starts with 0 
 */
void RPN::print(int depth) {
    // indent and print opening parenthesis
    this->indent(depth);
    if (!this->is_leaf()) {
        cout << "(";
    }
    // print the actual value
    cout << this->value << endl;

    if (this->is_leaf()) {
        return;
    }

    if (this->is_unary_op()) {
        this->right->print();
    } else {
        if (this->left->is_leaf() && !this->right->is_leaf()) {
            this->right->print(depth + 1);
            this->left->print(depth + 1);
        } else {
            this->left->print(depth + 1);
            this->right->print(depth + 1);
        }
    }

    // indent and print closing parenthesis
    this->indent(depth);
    if (!this->is_leaf()) {
        cout << ")" << endl;
    }
}

bool RPN::is_leaf() {
    return (this->is_number() && !this->left && !this->right) ||
           (this->is_number() && !this->right);
}

bool RPN::is_last_tree() {
    return this->is_binary_op() &&
           this->left->is_leaf() && this->right->is_leaf();
}

/**
 * @brief check if a string is a number (i.e. float)
 * 
 * @param str the string to check
 * @return true if string is numeric
 * @return false otherwise
 */
bool RPN::is_number() {
    try {
        stof(this->value);
    } catch (const std::invalid_argument& e) {
        return false;
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
