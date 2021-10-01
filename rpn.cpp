#include "rpn.h"
#include <iostream>

int main() {
	string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"}; 
	double result = rpn(test);
	cout << result << endl;
}
