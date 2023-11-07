#include "stfcpp/include/stfcpp/stfcpp.h"
#include "Pulsarion.h"

#include <crtdbg.h>

int main(int argc, char** argv) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Pulsarion::Initializers::InitLogger();

    auto results = STF_RUN_SUITE_TESTS();
    stfcpp::print_suite_test_details(results);
    return 0;
}
