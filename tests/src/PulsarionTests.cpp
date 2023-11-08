#include "stfcpp/include/stfcpp/stfcpp.h"
#include "Pulsarion.h"

int main(int argc, char** argv) {
    Pulsarion::Initializers::InitLogger();

    auto results = STF_RUN_SUITE_TESTS();
    stfcpp::print_suite_test_details(results);
    return 0;
}
