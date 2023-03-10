#include <catch2/catch_all.hpp>
#include <source.h>

TEST_CASE("Parsing") {
    std::vector<std::vector<std::string>> data_actual;
    std::vector<std::string> cells_actual;

    std::string str = "file.csv";
    Parse(cells_actual, data_actual, str.data());

    std::vector<std::string> cells_expected = {"", "A", "B", "Cell"};
    std::vector<std::vector<std::string>> data_expected = {{"1", "1", "0", "1"}, {"2", "2", "=A1+Cell30", "0"}, {"30", "0", "=B1+A1", "5"}};

    REQUIRE(cells_actual == cells_expected);
    REQUIRE(data_actual == data_expected);

}

TEST_CASE("Counting") {
    std::vector<std::vector<std::string>> data_actual = {{"1", "1", "0", "1"}, {"2", "2", "=A1+Cell30", "0"}, {"30", "0", "=B1+A1", "5"}};
    std::vector<std::string> cells_actual = {"", "A", "B", "Cell"};

    for (int out = 0; out < data_actual.size(); ++out) {
        for (int in = 0; in < data_actual[0].size(); ++in) {

            if (data_actual[out][in][0] == '=') {

                Convert(cells_actual, data_actual, out, in);
            }
        }
    }

    std::vector<std::vector<std::string>> data_expected = {{"1", "1", "0", "1"}, {"2", "2", "6", "0"}, {"30", "0", "1", "5"}};

    REQUIRE(data_actual == data_expected);
}
