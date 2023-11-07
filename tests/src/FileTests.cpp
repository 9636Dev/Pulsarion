#include "stfcpp/include/stfcpp/stfcpp.h"
#include "Pulsarion.h"

#include <string>

STF_TEST_SUITE(FileTests)
{
    inline static const std::string test_file = "files/file_tests/test.txt";

    void setup() override {
        Pulsarion::File file(test_file);
        file.CreateDirectories();
        if (file.Exists()) file.Delete();
    }

    void finish() override {
        Pulsarion::File file(test_file);
        if (file.Exists()) file.Delete();
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
        STF_BASIC_ASSERT(true, file.Delete(), "Could not delete file!");
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
        file.SetContent(content);
        
        std::string read_contents = file.GetContent();
        STF_BASIC_ASSERT(content, read_contents, "File content does not match!");
    }
    STF_SUITE_TEST(FileBasicReadWriteTest, test_basic_read_write);
};
STF_REGISTER_SUITE(FileTests);
