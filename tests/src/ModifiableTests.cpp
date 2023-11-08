#include "Pulsarion.h"
#include "stfcpp/include/stfcpp/stfcpp.h"

STF_TEST_SUITE(ModifiableTests)
{
    void test_creation()
    {
        Pulsarion::Modifiable<int> a = Pulsarion::Modifiable<int>::Create();
        STF_BASIC_ASSERT(0, a.GetConst(), "Default value was not 0!");

        Pulsarion::Modifiable<int> b = Pulsarion::Modifiable<int>::Create(5);
        STF_BASIC_ASSERT(5, b.GetConst(), "Constructed value was not 5!");

        Pulsarion::Modifiable<bool> c = Pulsarion::Modifiable<bool>::Create();
        STF_BASIC_ASSERT(false, c.GetConst(), "Default value was not false!");

        Pulsarion::Modifiable<bool> d = Pulsarion::Modifiable<bool>::Create(true);
        STF_BASIC_ASSERT(true, d.GetConst(), "Constructed value was not true!");

        Pulsarion::Modifiable<std::string> e = Pulsarion::Modifiable<std::string>::Create();
        STF_BASIC_ASSERT(std::string(""), e.GetConst(), "Default value was not empty!");

        Pulsarion::Modifiable<std::string> f = Pulsarion::Modifiable<std::string>::Create("Hello World!");
        STF_BASIC_ASSERT(std::string("Hello World!"), f.GetConst(), "Constructed value was not \"Hello World!\"!");
    }
    STF_SUITE_TEST(CreationTest, test_creation);
};
STF_REGISTER_SUITE(ModifiableTests);
