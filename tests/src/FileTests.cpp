#include "stfcpp/include/stfcpp/stfcpp.h"
#include "Pulsarion.h"

#include <string>

STF_TEST_SUITE(FileTests)
{
    inline static const std::string test_file = "files/file_tests/test.txt";

    void setup() override {
        Pulsarion::File file(test_file);
        
        if (!file.GetParent().Exists())
        {
            auto dir_results = file.GetParent().CreateDirectories();
            if (dir_results.IsFailure())
                stfcpp::logger::warn("Could not create test directory: " + dir_results.GetFailure()->message());
        }
        if (file.Exists())
        {
            auto result = file.Delete();
            if (result.IsFailure())
                STF_ASSERT_FAIL("Could not delete test file!");
        }
    }

    void finish() override {

    }

    
    void test_creation()
    {
        Pulsarion::File file(test_file);
        STF_BASIC_ASSERT(false, file.Exists(), "File existed before creation!");
        STF_BASIC_ASSERT(true, file.CreateNewFile(), "Could not create new file!");
        STF_BASIC_ASSERT(true, file.Exists(), "File does not exist after creation!");
    }
    STF_SUITE_TEST(FileExistsTest, test_creation);

    void test_deletion()
    {
        Pulsarion::File file(test_file);
        STF_BASIC_ASSERT(false, file.Exists(), "File existed before creation!");
        STF_BASIC_ASSERT(true, file.CreateNewFile(), "Could not create new file!");
        STF_BASIC_ASSERT(true, file.Exists(), "File does not exist after creation!");
        auto deleteResult = file.Delete();
        STF_BASIC_ASSERT_ONFAIL(true, deleteResult.IsSuccess() && deleteResult.Get(), [deleteResult]() mutable {
            STF_ASSERT_FAIL("Could not delete file: " + deleteResult.GetFailure()->message());
            });
        STF_BASIC_ASSERT(false, file.Exists(), "File existed after deletion!");
    }
    STF_SUITE_TEST(FileDeletionTest, test_deletion);

    void test_basic_read_write()
    {
        Pulsarion::File file(test_file);
        STF_BASIC_ASSERT(false, file.Exists(), "File exists before creation!");
        STF_BASIC_ASSERT(true, file.CreateNewFile(), "Could not create new file!");
        STF_BASIC_ASSERT(true, file.Exists(), "File does not exist after creation!");

        
        std::string content = "This is a test line!";
        STF_BASIC_ASSERT(true, file.SetContent(content), "Could not set file content!");
        
        auto read_results = file.GetContent();
        STF_BASIC_ASSERT(true, read_results.has_value(), "Could not read file content!");
        STF_BASIC_ASSERT(content, read_results.value(), "File content does not match!");
    }
    STF_SUITE_TEST(FileBasicReadWriteTest, test_basic_read_write);

    void test_cached_read_write()
    {
        Pulsarion::File file(test_file);

        STF_BASIC_ASSERT(false, file.IsUsingCachedContent(), "File is using cached content by default!");
        file.SetCacheContent(true);
        STF_BASIC_ASSERT(true, file.IsUsingCachedContent(), "File is not using cached content after setting it to true!");
        STF_BASIC_ASSERT(false, file.Exists(), "File exists before creation!");
        STF_BASIC_ASSERT(true, file.CreateNewFile(), "Could not create new file!");
        STF_BASIC_ASSERT(true, file.Exists(), "File does not exist after creation!");


        std::string content = "This is a test line!";
        STF_BASIC_ASSERT(true, file.SetContent(content), "Could not set file content!");

        // Second file to get actual file content
        Pulsarion::File file2(test_file);
        STF_BASIC_ASSERT(false, file2.IsUsingCachedContent(), "File is using cached content by default!");\
        auto read_results_nc = file2.GetContent();
        STF_BASIC_ASSERT(false, read_results_nc.has_value(), "Cached write wrote to file directly!");

        auto read_results = file.GetContent();
        STF_BASIC_ASSERT(true, read_results.has_value(), "Could not read file content!");
        STF_BASIC_ASSERT(content, read_results.value(), "File content does not match!");
        STF_BASIC_ASSERT(true, file.UpdateContent(), "Could not update file content!");
        auto read_results_nc2 = file2.GetContent();
        STF_BASIC_ASSERT(true, read_results_nc2.has_value(), "Could not read file content!");
        STF_BASIC_ASSERT(content, read_results_nc2.value(), "File content does not match!");

        std::string new_content = "This is a new test line!";
        STF_BASIC_ASSERT(true, file.SetContent(content), "Could not set file content!");
        auto read_results_nc3 = file2.GetContent();
        STF_BASIC_ASSERT(true, read_results_nc3.has_value(), "Could not read file content!");
        STF_BASIC_ASSERT(content, read_results_nc3.value(), "File content does not match!");

        auto new_read_results = file.GetContent();
        STF_BASIC_ASSERT(true, new_read_results.has_value(), "Could not read file content!");
        STF_BASIC_ASSERT(content, new_read_results.value(), "File content does not match!");
        STF_BASIC_ASSERT(true, file.UpdateContent(), "Could not update file content!");

        auto new_read_results_nc = file2.GetContent();
        STF_BASIC_ASSERT(true, new_read_results_nc.has_value(), "Could not read file content!");
        STF_BASIC_ASSERT(content, new_read_results_nc.value(), "File content does not match!");
    }
};
STF_REGISTER_SUITE(FileTests);
