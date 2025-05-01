#include "../CLIlib.h"

// has to be included after all other includes
#include "../../googletest/googletest/include/gtest/gtest.h"

auto cli = CLI::CLI::get_instance();
std::list<CLI::CLI::token> expected_token_list;

void clear_all()
{
    expected_token_list.clear();
    cli->clear();
}

TEST(CLI_EmptyOptionsNoValidation, NoArgumentsGiven)
{
    // Arrange
    clear_all();
    // In console: app_name
    const char* args_pack[] = {""};
    // expected_token_list is empty

    // Act
    EXPECT_NO_THROW(cli->parse_args(1, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

int main(int argc, char** argv)
{
    // inits googletest framework
    testing::InitGoogleTest(&argc, argv);

    // runs all tests
    return RUN_ALL_TESTS();
}
