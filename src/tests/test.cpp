#include "../CLIlib.h"

// has to be included after all other includes
#include "gtest/gtest.h"

/* TODO list:
 *
 * TestingEmptyArguments
 *
 * - OneMinus: app_name -
 *
 * - TwoMinuses: app_name --
 *
 * - ThreeMinuses: app_name ---
 *
 * - ShortKeyWithOneMinusAfter: app_name -k -
 *
 * - OneMinus: app_name -- -e
 *
 * - OneMinus: app_name -
 */

auto cli = CLI::CLI::get_instance();
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

int main(int argc, char** argv)
{
    // inits googletest framework
    testing::InitGoogleTest(&argc, argv);

    // runs all tests
    return RUN_ALL_TESTS();
}
