#include "../CLIlib.h"
#include <list>

// has to be included after all other includes
#include "../../googletest/googletest/include/gtest/gtest.h"

auto cli = CLI::CLI::get_instance();
std::list<CLI::CLI::token> expected_token_list;

void clear_all()
{
    expected_token_list.clear();
    cli->clear();
}

TEST(CLI_EmptyArgvNoValidation, NoArgumentsGiven)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {""};

    // Act (empty for this test)
    EXPECT_NO_THROW(cli->parse_args(1, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyArgvNoValidation, EmptyShortKeyGiven)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-"};

    // Act (empty for this test)
    EXPECT_THROW(cli->parse_args(2, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyArgvNoValidation, EmptyShortKeyGivenWithNoEmptyBefore)
{
    // Arrange
    clear_all();
    expected_token_list = {{"k", ""}};
    const char* args_pack[] = {"", "-k", "-"};

    // Act (empty for this test)
    EXPECT_THROW(cli->parse_args(3, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyArgvNoValidation, EmptyShortKeyGivenWithNoEmptyAfter)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-", "-e"};

    // Act (empty for this test)
    EXPECT_THROW(cli->parse_args(3, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyArgvNoValidation, EmptyLongOptionGiven)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "--"};

    // Act (empty for this test)
    EXPECT_THROW(cli->parse_args(2, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyArgvNoValidation, EmptyLongOptionGivenWithNoEmptyBefore)
{
    // Arrange
    clear_all();
    expected_token_list = {{"param", ""}};
    const char* args_pack[] = {"", "--param", "--"};

    // Act (empty for this test)
    EXPECT_THROW(cli->parse_args(3, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyArgvNoValidation, EmptyLongOptionGivenWithNoEmptyAfter)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "--", "--param"};

    // Act (empty for this test)
    EXPECT_THROW(cli->parse_args(3, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyLowerCase)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-t"};
    expected_token_list.emplace_back("t", "");

    // Act
    ASSERT_NO_THROW(cli->parse_args(2, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyUpperCase)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-H"};
    expected_token_list.emplace_back("H", "");

    // Act
    ASSERT_NO_THROW(cli->parse_args(2, const_cast<char**>(args_pack)));

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
