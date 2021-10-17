#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RPN {
   private:
    std::string value;

    // for binary operators
    RPN* left = nullptr;  // always null if unary operator
    RPN* right = nullptr;

    bool is_leaf() {
        return (this->is_number() && !this->left && !this->right) ||
               (this->is_number() && !this->right);
    }

    bool is_last_tree() {
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
    bool is_number() {
        try {
            stof(this->value);
        } catch (const std::invalid_argument& e) {
            return false;
        }
        return true;
    }

    /**
     * @brief check if a string is an singleton operator
     *
     * @param str the string to check
     * @return true if string is operator
     * @return false otherwise
     */
    bool is_unary_op() {
        return this->value == "<" || this->value == ">";
    }

    /**
     * @brief check if a string is an binary operator
     *
     * @param str the string to check
     * @return true if string is operator
     * @return false otherwise
     */
    bool is_binary_op() {
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
     * @brief check if the parse tree is valid
     */
    bool is_tree_valid() {
        // base case
        // a numeric node must be leaf (has no child)
        if (this->is_number() && !this->left && !this->right) {
            return true;
        }

        // if the current node is a unary operator,
        //   then this child must exists be valid for it to be valid
        // if binary operator
        //   both left and right have to exists and valid for it to be valid
        if (this->is_unary_op()) {
            return this->right && this->right->is_tree_valid();
        } else if (this->is_binary_op()) {
            return this->right && this->right->is_tree_valid() &&
                   this->left && this->left->is_tree_valid();
        }
        return false;
    }

    /**
     * @brief count the node of this tree
     */
    int get_node_count() {
        if (this->is_leaf()) {
            return 1;
        }

        if (this->is_unary_op()) {
            return 1 + this->right->get_node_count();
        }

        return 1 + this->left->get_node_count() + this->right->get_node_count();
    }

    /**
     * @brief helper function of print,
     * indent the line according to depth.
     * NOTE: two space indentation
     *
     * @param depth the level of the node, the root starts with 0
     */
    void indent(int depth) {
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
    void print(int depth) {
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
            this->right->print(depth + 1);
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

   public:
    /**
     * @brief Construct a new RPN object
     * with depth to help syntax checking
     *
     * @param strs
     * @param depth
     */
    RPN(vector<string>& strs, int depth) {
        // base case
        if (strs.empty()) {
            return;
        }
        int len = strs.size();
        this->value = strs.back();
        strs.pop_back();

        if (this->is_number()) {
            return;
        }

        if (this->is_unary_op()) {
            this->right = new RPN(strs, depth + 1);
        } else if (this->is_binary_op()) {
            this->right = new RPN(strs, depth + 1);
            this->left = new RPN(strs, depth + 1);
        } else {
            string err_msg = "operator/operand not supported (" + this->value + ")";
            throw err_msg;
        }

        if (!this->is_tree_valid() || (depth == 0 && len != this->get_node_count())) {
            throw "Invalid syntax";
        }
    }

    RPN(std::vector<std::string>& strs) : RPN(strs, 0) {}
    RPN(std::string);

    double calculate() {
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
            if (b == 0) {
                throw "Arithmetic: denominator cannot be 0.";
            }
            result = a / b;
        } else if (this->value == "**") {
            if (a == 0 || (a == -1 && b < 1 && b > -1)) {
                throw "Arithmetic: denominator cannot be 0.";
            }
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
    void print() {
        // start printing the tree at the root
        this->print(0);
    }

    ~RPN() {
        if (this->left) {
            delete this->left;
        }
        if (this->right) {
            delete this->right;
        }
    }
};

/******** handler function ******/
double rpn(string* strs, int n, bool is_print_needed) {
    // construct a vector for the RPN constructor
    vector<string> elements;
    for (int i = 0; i < n; i++) {
        elements.push_back(strs[i]);
    }

    // try to build the parse tree
    RPN* model;
    double res;
    try {
        model = new RPN(elements);
        if (is_print_needed) {
            model->print();
        }
        res = model->calculate();
    } catch (const string& msg) {
        throw msg;
    } catch (const char* msg) {
        throw msg;
    } catch (...) {
        // swallow it
    }

    return res;
}
