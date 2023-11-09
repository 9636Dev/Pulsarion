#include <Pulsarion.h>
#include "stfcpp/include/stfcpp/stfcpp.h"

STF_TEST_SUITE(ModifiableTests)
{
    static void test_creation()
    {
        Pulsarion::Modifiable<int> a = Pulsarion::Modifiable<int>::Create();
        STF_BASIC_ASSERT(true, a.IsDirty(), "Constructed value was not dirty!");
        STF_BASIC_ASSERT(0, a.GetConst(), "Default value was not 0!");

        Pulsarion::Modifiable<int> b = Pulsarion::Modifiable<int>::Create(5);
        STF_BASIC_ASSERT(true, b.IsDirty(), "Constructed value was not dirty!");
        STF_BASIC_ASSERT(5, b.GetConst(), "Constructed value was not 5!");

        Pulsarion::Modifiable<bool> c = Pulsarion::Modifiable<bool>::Create();
        STF_BASIC_ASSERT(true, c.IsDirty(), "Constructed value was not dirty!");
        STF_BASIC_ASSERT(false, c.GetConst(), "Default value was not false!");

        Pulsarion::Modifiable<bool> d = Pulsarion::Modifiable<bool>::Create(true);
        STF_BASIC_ASSERT(true, d.IsDirty(), "Constructed value was not dirty!");
        STF_BASIC_ASSERT(true, d.GetConst(), "Constructed value was not true!");

        Pulsarion::Modifiable<std::string> e = Pulsarion::Modifiable<std::string>::Create();
        STF_BASIC_ASSERT(true, e.IsDirty(), "Constructed value was not dirty!");
        STF_BASIC_ASSERT(std::string(""), e.GetConst(), "Default value was not empty!");

        Pulsarion::Modifiable<std::string> f = Pulsarion::Modifiable<std::string>::Create("Hello World!");
        STF_BASIC_ASSERT(true, f.IsDirty(), "Constructed value was not dirty!");
        STF_BASIC_ASSERT(std::string("Hello World!"), f.GetConst(), "Constructed value was not \"Hello World!\"!");
    }
    STF_SUITE_TEST(CreationTest, test_creation);

    static void test_emplace()
    {
        Pulsarion::Modifiable<int> a(6);
        STF_BASIC_ASSERT(false, a.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(6, a.GetConst(), "Moved in value was not 6!");

        Pulsarion::Modifiable<bool> b(true);
        STF_BASIC_ASSERT(false, b.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(true, b.GetConst(), "Moved in value was not true!");

        Pulsarion::Modifiable<std::string> c("Hello World!");
        STF_BASIC_ASSERT(false, c.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(std::string("Hello World!"), c.GetConst(), "Moved in value was not \"Hello World!\"!");
    }
    STF_SUITE_TEST(EmplaceTest, test_emplace);

    static void test_get()
    {
        Pulsarion::Modifiable<int> a(2);
        STF_BASIC_ASSERT(false, a.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(2, a.GetConst(), "Moved in value was not 2!");
        STF_BASIC_ASSERT(2, a.Get(), "Moved in value was not 2!");
        STF_BASIC_ASSERT(true, a.IsDirty(), "Value after calling 'get' was not dirty!");

        Pulsarion::Modifiable<bool> b(true);
        STF_BASIC_ASSERT(false, b.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(true, b.GetConst(), "Moved in value was not true!");
        STF_BASIC_ASSERT(true, b.Get(), "Moved in value was not true!");
        STF_BASIC_ASSERT(true, b.IsDirty(), "Value after calling 'get' was not dirty!");

        Pulsarion::Modifiable<std::string> c("Hello World!");
        STF_BASIC_ASSERT(false, c.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(std::string("Hello World!"), c.GetConst(), "Moved in value was not \"Hello World!\"!");
        STF_BASIC_ASSERT(std::string("Hello World!"), c.Get(), "Moved in value was not \"Hello World!\"!");
        STF_BASIC_ASSERT(true, c.IsDirty(), "Value after calling 'get' was not dirty!");
    }
    STF_SUITE_TEST(GetTest, test_get);

    static void test_set()
    {
        Pulsarion::Modifiable<int> a(3);
        STF_BASIC_ASSERT(false, a.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(3, a.GetConst(), "Moved in value was not 3!");
        a.Set(4);
        STF_BASIC_ASSERT(true, a.IsDirty(), "Value after calling 'set' was not dirty!");
        STF_BASIC_ASSERT(4, a.GetConst(), "Value after calling 'set' was not 4!");

        Pulsarion::Modifiable<bool> b(true);
        STF_BASIC_ASSERT(false, b.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(true, b.GetConst(), "Moved in value was not true!");
        b.Set(false);
        STF_BASIC_ASSERT(true, b.IsDirty(), "Value after calling 'set' was not dirty!");
        STF_BASIC_ASSERT(false, b.GetConst(), "Value after calling 'set' was not false!");

        Pulsarion::Modifiable<std::string> c("Hello World!");
        STF_BASIC_ASSERT(false, c.IsDirty(), "Moved in value was dirty!");
        STF_BASIC_ASSERT(std::string("Hello World!"), c.GetConst(), "Moved in value was not \"Hello World!\"!");
        c.Set("Hello World! 2");
        STF_BASIC_ASSERT(true, c.IsDirty(), "Value after calling 'set' was not dirty!");
        STF_BASIC_ASSERT(std::string("Hello World! 2"), c.GetConst(), "Value after calling 'set' was not \"Hello World! 2\"!");
    }
    STF_SUITE_TEST(SetTest, test_set);
};
STF_REGISTER_SUITE(ModifiableTests);
