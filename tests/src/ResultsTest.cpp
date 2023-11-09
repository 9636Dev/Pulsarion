#include <stfcpp/include/stfcpp/stfcpp.h>
#include <Pulsarion.h>

STF_TEST_SUITE(ResultsTest)
{
    static void test_creation()
    {
        Pulsarion::Result<bool, int> a = Pulsarion::Result<bool, int>::Ok(true);
        STF_BASIC_ASSERT(true, a.IsSuccess(), "Constructed value was not Ok!");
        STF_BASIC_ASSERT(false, a.IsFailure(), "Constructed value was failure!");
        STF_BASIC_ASSERT(true, a.Get().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(true, a.Get().value(), "Constructed value was not true!");

        Pulsarion::Result<bool, int> b = Pulsarion::Result<bool, int>::Fail(5);
        STF_BASIC_ASSERT(false, b.IsSuccess(), "Constructed value was success!");
        STF_BASIC_ASSERT(true, b.IsFailure(), "Constructed value was not failure!");
        STF_BASIC_ASSERT(true, b.GetFailure().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(5, b.GetFailure().value(), "Constructed value was not 5!");

        // Same type for success and error
        Pulsarion::Result<int, int> c = Pulsarion::Result<int, int>::Ok(5);
        STF_BASIC_ASSERT(true, c.IsSuccess(), "Constructed value was not Ok!");
        STF_BASIC_ASSERT(false, c.IsFailure(), "Constructed value was failure!");
        STF_BASIC_ASSERT(true, c.Get().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(5, c.Get().value(), "Constructed value was not 5!");

        Pulsarion::Result<int, int> d = Pulsarion::Result<int, int>::Fail(5);
        STF_BASIC_ASSERT(false, d.IsSuccess(), "Constructed value was success!");
        STF_BASIC_ASSERT(true, d.IsFailure(), "Constructed value was not failure!");
        STF_BASIC_ASSERT(true, d.GetFailure().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(5, d.GetFailure().value(), "Constructed value was not 5!");
    }
    STF_SUITE_TEST(CreationTest, test_creation);

    static void test_constructor()
    {
        Pulsarion::Result<bool, int> a(true);
        STF_BASIC_ASSERT(true, a.IsSuccess(), "Constructed value was not Ok!");
        STF_BASIC_ASSERT(false, a.IsFailure(), "Constructed value was failure!");
        STF_BASIC_ASSERT(true, a.Get().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(true, a.Get().value(), "Constructed value was not true!");

        Pulsarion::Result<bool, int> b(5);
        STF_BASIC_ASSERT(false, b.IsSuccess(), "Constructed value was success!");
        STF_BASIC_ASSERT(true, b.IsFailure(), "Constructed value was not failure!");
        STF_BASIC_ASSERT(true, b.GetFailure().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(5, b.GetFailure().value(), "Constructed value was not 5!");

        // Same type for success and error
        Pulsarion::Result<int, int> c(5, Pulsarion::OkTag{});
        STF_BASIC_ASSERT(true, c.IsSuccess(), "Constructed value was not Ok!");
        STF_BASIC_ASSERT(false, c.IsFailure(), "Constructed value was failure!");
        STF_BASIC_ASSERT(true, c.Get().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(5, c.Get().value(), "Constructed value was not 5!");

        Pulsarion::Result<int, int> d(5, Pulsarion::FailTag{});
        STF_BASIC_ASSERT(false, d.IsSuccess(), "Constructed value was success!");
        STF_BASIC_ASSERT(true, d.IsFailure(), "Constructed value was not failure!");
        STF_BASIC_ASSERT(true, d.GetFailure().has_value(), "Constructed value did not have a value!");
        STF_BASIC_ASSERT(5, d.GetFailure().value(), "Constructed value was not 5!");
    }
    STF_SUITE_TEST(ConstructorTest, test_constructor);
};
STF_REGISTER_SUITE(ResultsTest);