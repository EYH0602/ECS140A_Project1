#include <iostream>
#include <string>
#include <vector>

double rpn(std::vector<std::string>);

class RPN {
   private:
    std::string value;

	// for binary operators
	RPN* left = nullptr;
	RPN* right = nullptr;

    bool isLeaf();
    bool isLastTree();

   public:
    RPN(std::vector<std::string>&);
	RPN(std::string);
    double calculate();
	void print();
};
