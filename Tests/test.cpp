#include <catch2/catch_all.hpp>
#include <source.h>

TEST_CASE("Basic") {
    std::vector<std::vector<std::string>> data_actual;
    std::vector<std::string> cells_actual;

    std::string str = "reportcard.csv";
    Parse(cells_actual, data_actual, str.data());

    std::vector<std::string> cells_expected = {"", "A", "B", "Cell"};
    std::vector<std::vector<std::string>> data_expected = {{"1", "1", "0", "1"}, {"2", "2", "=A1+Cell30", "0"}, {"30", "0", "=B1+A1", "5"}};

    REQUIRE(cells_actual == cells_expected);
    REQUIRE(data_actual == data_expected);

}
