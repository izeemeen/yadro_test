#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

                /*** Parsing file.csv ***/

void Parse(std::vector<std::string>& column, std::vector<std::vector<std::string> >& data,
    char* arg) {

    std::fstream fin;

    fin.open(arg, std::ios::in);
    if (!fin) {
        std::cout << "Incorrect format || Incorrect path";
        exit(0);
    }

    std::vector<std::string> row;
    std::string line, word;

    getline(fin, line);
    std::stringstream s(line);
    while (getline(s, word, ',')) {
        column.push_back(word);
    }

    while (getline(fin, line)) {

        row.clear();

        std::stringstream str(line);

        while (getline(str, word, ',')) {
            row.push_back(word);
        }
        data.push_back(row);
    }
}


                /*** Function to count values in cells with recursive call ***/

void Convert(std::vector<std::string>& column, std::vector<std::vector<std::string> >& data,
    int out, int in) {

    std::string current = data[out][in];
    int iterator = 1;
    std::string cell;

    int first = 0;
    int second = 0;
    int col_one, col_two;
    int number_one, number_two;

    bool flag = false;

                    /*** Count arg1 ***/
    while (std::isdigit(current[iterator])) {
        first += data[out][in][iterator] - '0';
        ++iterator;
    }

    if (first == 0) {
        while (std::isalpha(current[iterator])) {
            cell += current[iterator];
            ++iterator;
        }

        for (int col_num = 1; col_num < column.size(); ++col_num) {
            if (column[col_num] == cell) {
                col_one = col_num;
                flag = true;
                break;
            }
        }

        if (!flag) {
            std::cout << "Invalid cell address!";
            exit(0);
        }

        flag = false;
        cell.clear();

        while (std::isdigit(current[iterator])) {
            cell += current[iterator];
            ++iterator;
        }

        for (int col_num = 0; col_num < data.size(); ++col_num) {
            if (data[col_num][0] == cell) {
                number_one = col_num;
                flag = true;
                break;
            }
        }

        if (!flag) {
            std::cout << "Invalid cell address!";
            exit(0);
        }

        flag = false;

        if (number_one >= data.size() || col_one >= data[0].size()) {
            std::cout << "Wrong table format!";
            exit(0);
        }

        if (data[number_one][col_one][0] == '=') {
            Convert(column, data, number_one, col_one);
        }

        first = std::stoi(data[number_one][col_one]);
    }

                    /*** Count math sign ***/
    char sign = data[out][in][iterator];

    ++iterator;
    if (!std::isdigit(data[out][in][iterator]) && !std::isalpha(data[out][in][iterator])) {
        std::cout << "Wrong operation!";
        exit(0);
    }

    cell.clear();

                    /*** Count Arg2 ***/
    while (std::isdigit(current[iterator])) {
        second += data[out][in][iterator] - '0';
        ++iterator;
    }

    if (second == 0) {
        while (std::isalpha(current[iterator])) {
            cell += current[iterator];
            ++iterator;
        }

        for (int col_num = 1; col_num < column.size(); ++col_num) {
            if (column[col_num] == cell) {
                col_two = col_num;
                flag = true;
                break;
            }
        }

        if (!flag) {
            std::cout << "Invalid cell address!";
            exit(0);
        }

        flag = false;
        cell.clear();

        while (std::isdigit(current[iterator])) {
            cell += current[iterator];
            ++iterator;
        }

        for (int col_num = 0; col_num < data.size(); ++col_num) {
            if (data[col_num][0] == cell) {
                number_two = col_num;
                flag = true;
                break;
            }
        }

        if (!flag) {
            std::cout << "Invalid cell address!";
            exit(0);
        }

        if (number_two >= data.size() || col_two >= data[0].size()) {
            std::cout << "Wrong table format!";
            exit(0);
        }

        if (data[number_two][col_two][0] == '=') {
            Convert(column, data, number_two, col_two);
        }

        second = std::stoi(data[number_two][col_two]);
    }

                    /*** Count expression ***/
    switch (sign) {
    case '+':
        data[out][in] = std::to_string(first + second);
        break;
    case '-':
        data[out][in] = std::to_string(first - second);
        break;
    case '*':
        data[out][in] = std::to_string(first * second);
        break;
    case '/':
        if (second == 0) {
            std::cout << "Division by zero!";
            exit(0);
        }

        break;
    default:
        std::cout << "Wrong operation!";
        exit(0);

    }
}



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
            if (in != data[0].size()) {
                std::cout << ',';
            }
        }
        std::cout << '\n';
    }

    return 0;
}