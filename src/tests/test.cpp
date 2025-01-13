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
    const char* args_pack[] = {""};

    // Act
    EXPECT_NO_THROW(cli->parse_args(1, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, EmptyShortKeyGiven)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-"};

    // Act
    EXPECT_THROW(cli->parse_args(2, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, EmptyShortKeyGivenWithNoEmptyBefore)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-k", "-"};
    expected_token_list = {{"k", ""}};

    // Act
    EXPECT_THROW(cli->parse_args(3, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, EmptyShortKeyGivenWithNoEmptyAfter)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-", "-e"};

    // Act
    EXPECT_THROW(cli->parse_args(3, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, EmptyLongOptionGiven)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "--"};

    // Act
    EXPECT_THROW(cli->parse_args(2, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, EmptyLongOptionGivenWithNoEmptyBefore)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "--param", "--"};
    expected_token_list = {{"param", ""}};

    // Act
    EXPECT_THROW(cli->parse_args(3, const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, EmptyLongOptionGivenWithNoEmptyAfter)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "--", "--param"};

    // Act
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
    expected_token_list = {{"t", ""}};

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
    expected_token_list = {{"H", ""}};

    // Act
    ASSERT_NO_THROW(cli->parse_args(2, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyWithNearNumberValue)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-t23"};
    expected_token_list = {{"t", "23"}};

    // Act
    ASSERT_NO_THROW(cli->parse_args(2, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyWithFarNumberValue)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-B", "98"};
    expected_token_list = {{"B", "98"}};

    // Act
    ASSERT_NO_THROW(cli->parse_args(3, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyWithNearSomeNumberValues)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-k89", "12", "34", "52"};
    expected_token_list = {{"k", "89"}, {"k", "12"}, {"k", "34"}, {"k", "52"}};

    // Act
    ASSERT_NO_THROW(cli->parse_args(5, const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortKeysNoValidation, SingleShortKeyWithFarSomeNumberValues)
{
    // Arrange
    clear_all();
    const char* args_pack[] = {"", "-k", "12", "34", "52"};
    expected_token_list = {{"k", "12"}, {"k", "34"}, {"k", "52"}};

    // Act
    ASSERT_NO_THROW(cli->parse_args(5, const_cast<char**>(args_pack)));

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
