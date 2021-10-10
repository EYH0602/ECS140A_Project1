
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include "rpn.h"
using namespace std;

vector<string> parse_csv(string line) {
    stringstream ss(line);
    vector<string> res;
    while (ss.good()) {
        string temp;
        getline(ss, temp, ',');
        res.push_back(temp);
    }
    return res;
}

/**
 * Display the prompt at begining of line.
 * NOTE: this part is the same from my old project:
 * https://github.com/EYH0602/gunrock_web/blob/main/dcash_wallet/wallet.cpp
 * @param prompt Your prompt with ending charactor '\0'.
 */
#define SHOW_PROMPT(prompt) write(STDOUT_FILENO, prompt, strlen(prompt))

/**
 * @brief start the command environment of RPN calculator.
 * NOTE: this part is the same from my old project:
 * https://github.com/EYH0602/gunrock_web/blob/main/dcash_wallet/wallet.cpp
 * 
 * @param fp the file to read from 
 * (stdin for interactive mode, other for batch mode).
 * @param is_print_needed need to print the tree or not
 */
void start_app(FILE* fp, bool is_print_needed) {
    string prompt = (fp == stdin) ? "> " : "";
    size_t cap = 0;
    ssize_t len;
    char* buff = NULL;
    string line;
    vector<string> rpn_line;
    RPN* model;

    // read from file/STDIN line by line
    while (SHOW_PROMPT(prompt.c_str()), (len = getline(&buff, &cap, fp)) > 0) {
        if (len == 1 && buff[len] == '\0') {
            continue;
        }
        buff[len - 1] = '\0';
        rpn_line = parse_csv(string(buff));

        // try to build the parse tree
        try {
            model = new RPN(rpn_line);
        } catch (const string& msg) {
            cerr << "Error: " << msg << endl;
            continue;
        } catch (const char* msg) {
            cerr << "Error: " << msg << endl;
            continue;
        } catch (...) {
            // swallow it
        }

        // print and evaluate the postfix
        if (is_print_needed) {
            model->print();
        }
        cout << "Result: " << model->calculate() << endl;
        delete model;
    }
}

int main(int argc, char* argv[]) {
    // parse cli arguments
    int option;
    FILE* fp = stdin;
    bool is_print_needed = false;
    while ((option = getopt(argc, argv, "lf:")) != -1) {
        switch (option) {
            case 'l':
                is_print_needed = true;
                break;
            case 'f':
                fp = fopen(optarg, "r");
                break;
            default:
                break;
        }
    }

    start_app(fp, is_print_needed);

    // old test case
    // string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};
    // int n = 9;

    return 0;
}