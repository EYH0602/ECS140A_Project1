#include <string>
#include <vector>
#include <iostream>

double rpn(std::vector<std::string>);

class RPN {
	private:
		std::string value;

		bool isLeaf();
		bool isLastTree();

	public:
		RPN(std::vector<std::string>);
		double calculate();
};
