#include <iostream>
#include <string>
#include <vector>

double rpn(std::string *strs, int n);

class RPN {
   private:
    std::string value;

	// for binary operators
	RPN* left = nullptr;
	RPN* right = nullptr;

	// for single parameter operators
	RPN* next = nullptr;

    bool isLeaf();
    bool isLastTree();
	bool is_number();
	bool is_singleton_operator();
	bool is_binary_operator();

   public:
    RPN(std::vector<std::string>&);
	RPN(std::string);
    double calculate();
	void print();
};
