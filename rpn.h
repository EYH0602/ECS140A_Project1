#include <iostream>
#include <string>
#include <vector>

double rpn(std::string* strs, int n);

class RPN {
   private:
    std::string value;

    // for binary operators
    RPN* left = nullptr;  // always null if unary operator
    RPN* right = nullptr;

    bool is_leaf();
    bool is_last_tree();
    bool is_number();
    bool is_unary_op();
    bool is_binary_op();

   public:
    RPN(std::vector<std::string>&);
    RPN(std::string);
    double calculate();
    void print();
};
