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
 * TestingShortKeys
 *
 * + ValidShortKeyWithoutValue app_name -v
 *
 * + InvalidShortKeyWithoutValue app_name -i
 *
 * + ValidShortKeyWithNearValue app_name -k3
 *
 * + ValidShortKeyWithFarValue app_name -k 3
 *
 * TestingLongOptions
 *
 * + ValidLongOptionWithoutValue app_name --opt1
 *
 * + ValidTwoLongOptionsWithoutValues app_name --opt1 --opt2
 *
 * + InvalidTwoLongOptionsWithoutValues app_name --opt1 --opt2
 *
 * + ValidShortKeyWithTwoMinuses app_name --i
 *
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
    cli->add_short_option('k');
    expected_token_list = {{"k", "-"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingEmptyArguments, TwoMinusesWithShortKeyAfter)
{
    // Arrange
    reset_all();
    // In terminal: app_name -- -e
    const char* args_pack[] = {"", "-- -e"};
    cli->add_short_option('e');
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingShortKeys, ValidShortKeyWithoutValue)
{
    // Arrange
    reset_all();
    // In terminal: app_name -v
    const char* args_pack[] = {"", "-v"};
    cli->add_short_option('v');
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
    cli->add_short_option('v');
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingShortKeys, ValidShortKeyWithNearValue)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k3
    const char* args_pack[] = {"", "-k3"};
    cli->add_short_option('k');
    expected_token_list = {{"k", "3"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingShortKeys, ValidShortKeyWithFarValue)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k 3
    const char* args_pack[] = {"", "-k", "3"};
    cli->add_short_option('k');
    expected_token_list = {{"k", "3"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(TestingLongOptions, ValidLongOptionWithoutValue)
{
    // Arrange
    reset_all();
    // In terminal: app_name --opt1
    const char* args_pack[] = {"", "--opt1"};
    cli->add_long_option("opt1");
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
    cli->add_long_option("opt1");
    cli->add_long_option("opt2");
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

TEST(TestingLongOptions, ValidShortKeyWithTwoMinuses)
{
    // Arrange
    reset_all();
    // In terminal: app_name --o
    const char* args_pack[] = {"", "--o"};
    cli->add_short_option('o');
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
