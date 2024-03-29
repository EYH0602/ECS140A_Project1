#include <iostream>
#include <string>
#include <vector>

double rpn(std::string*, int, bool);

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
    bool is_tree_valid();

    int get_node_count();

    void indent(int);
    void print(int);

   public:
    RPN(std::vector<std::string>&);
    RPN(std::vector<std::string>&, int);
    RPN(std::string);
    double calculate();
    void print();
    ~RPN();
};
