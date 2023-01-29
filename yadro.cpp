#include <iostream>

#include "yadro/source.h"


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Wrong arguments!";
        return -1;
    }

    char* arg = argv[1];

    std::vector<std::string> column;
    std::vector<std::vector<std::string> > data;

    Parse(column, data, arg);

    for (int out = 0; out < data.size(); ++out) {
        for (int in = 0; in < data[0].size(); ++in) {

            if (data[out][in][0] == '=') {

                Convert(column, data, out, in);
            }
            else if ((data[out][in][0] != '=') && (!std::isdigit(data[out][in][0]))) {
                std::cout << "Invalid line!";
                exit(0);
            }
        }
    }

    for (int col = 0; col < column.size(); ++col) {
        std::cout << column[col];
        if (col != column.size() - 1) {
            std::cout << ',';
        }
    }

    std::cout << '\n';

    for (int out = 0; out < data.size(); ++out) {
        for (int in = 0; in < data[0].size(); ++in) {
            std::cout << data[out][in];
            if (in != data[0].size() - 1) {
                std::cout << ',';
            }
        }
        std::cout << '\n';
    }

    return 0;
}