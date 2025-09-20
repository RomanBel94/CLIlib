#include "../CLIlib.h"
#include <memory>

// has to be included after all other includes
#include "gtest/gtest.h"

/* TODO list:
 *
 * TestingEmptyArguments
 *
 * + OneMinus: app_name -
 *
 * + TwoMinuses: app_name --
 *
 * + ThreeMinuses: app_name ---
 *
 * + ShortKeyWithOneMinusAfter: app_name -k -
 *
 * + TwoMinusesWithShortKeyAfter: app_name -- -e
 *
 * + ValueWithoutKey: app_name value
 *
 * TestingShortKeys
 *
 * + ValidShortKeyWithoutValue app_name -v
 *
 * + InvalidShortKeyWithoutValue app_name -i
 *
 * TestingLongOptions
 *
 * + ValidLongOptionWithoutValue app_name --opt1
 *
 * + ValidTwoLongOptionsWithoutValues app_name --opt1 --opt2
 *
 * + InvalidTwoLongOptionsWithoutValues app_name --opt1 --opt2
 */

auto cli = std::make_unique<CLI::CLI>();
std::list<CLI::CLI::token> expected_token_list;

inline void reset_all()
{
    expected_token_list.clear();
    cli->clear();
}

TEST(TestingEmptyArguments, OneMinus)
{
    // Arrange
    reset_all();
    // In terminal: app_name -
    const char* args_pack[] = {"", "-"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingEmptyArguments, TwoMinuses)
{
    // Arrange
    reset_all();
    // In terminal: app_name --
    const char* args_pack[] = {"", "--"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingEmptyArguments, ThreeMinuses)
{
    // Arrange
    reset_all();
    // In terminal: app_name ---
    const char* args_pack[] = {"", "---"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingEmptyArguments, ShortKeyWithOneMinusAfter)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k -
    const char* args_pack[] = {"", "-k", "-"};
    cli->add_opt('k');
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingEmptyArguments, TwoMinusesWithShortKeyAfter)
{
    // Arrange
    reset_all();
    // In terminal: app_name -- -e
    const char* args_pack[] = {"", "-- -e"};
    cli->add_opt('e');
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingEmptyArguments, ValueWithoutKey)
{
    // Arrange
    reset_all();
    // In terminal: app_name value
    const char* args_pack[] = {"", "value"};
    cli->add_opt("");
    expected_token_list = {{"", "value"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingShortKeys, ValidShortKeyWithoutValue)
{
    // Arrange
    reset_all();
    // In terminal: app_name -v
    const char* args_pack[] = {"", "-v"};
    cli->add_opt("v");
    expected_token_list = {{"v", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingShortKeys, InvalidShortKeyWithoutValue)
{
    // Arrange
    reset_all();
    // In terminal: app_name -i
    const char* args_pack[] = {"", "-i"};
    cli->add_opt("v");
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingLongOptions, ValidLongOptionWithoutValue)
{
    // Arrange
    reset_all();
    // In terminal: app_name --opt1
    const char* args_pack[] = {"", "--opt1"};
    cli->add_long_opt("opt1");
    expected_token_list = {{"opt1", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingLongOptions, ValidTwoLongOptionsWithoutValues)
{
    // Arrange
    reset_all();
    // In terminal: app_name --opt1 --opt2
    const char* args_pack[] = {"", "--opt1", "--opt2"};
    cli->add_long_opt("opt1", "opt2");
    expected_token_list = {{"opt1", ""}, {"opt2", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingLongOptions, InvalidTwoLongOptionsWithoutValues)
{
    // Arrange
    reset_all();
    // In terminal: app_name --opt1 --opt2
    const char* args_pack[] = {"", "--opt1", "--opt2"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

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
