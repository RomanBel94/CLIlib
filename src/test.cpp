#include "CLIlib.h"
#include <list>

// has to be included after all other includes
#include "../googletest/googletest/include/gtest/gtest.h"

auto cli = CLI::CLI::get_instance();
std::list<CLI::CLI::token> expected_token_list;

void clear_all()
{
    expected_token_list.clear();
    cli->clear();
}

TEST(CLI_EmptyArgv, NoArgumentsGiven)
{
    // Arrange
    clear_all();
    const char* args_pack1[] = {""};

    // Act
    cli->parse_args(1, const_cast<char**>(args_pack1));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyLowerCase)
{
    // Arrange
    clear_all();
    const char* args_pack2[] = {"", "-t"};
    expected_token_list.emplace_back("t", "");

    // Act
    cli->parse_args(2, const_cast<char**>(args_pack2));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyUpperCase)
{
    // Arrange
    clear_all();
    const char* args_pack3[] = {"", "-H"};
    expected_token_list.emplace_back("H", "");

    // Act
    cli->parse_args(2, const_cast<char**>(args_pack3));

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
