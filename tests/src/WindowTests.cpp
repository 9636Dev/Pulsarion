#include <stfcpp/include/stfcpp/stfcpp.h>
#include <Pulsarion.h>

#include <memory>

STF_TEST_SUITE(WindowTests)
{
    void test_create_window()
    {
        std::unique_ptr<Pulsarion::Window> window = Pulsarion::CreateWindowPointer(Pulsarion::WindowProperties());
        window->Close();

    }
    STF_SUITE_TEST(CreateWindowTest, test_create_window);
};
STF_REGISTER_SUITE(WindowTests);