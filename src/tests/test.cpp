#include "../CLIlib.h"

// has to be included after all other includes
#include "../../googletest/googletest/include/gtest/gtest.h"

/* TODO:
 *
 * CLI_EmptyOptionsNoValidation
 *
 * 1. + app_name            (NoOptionsGiven)
 * 2. + app_name -          (OneMinusGiven)
 * 3. + app_name --         (TwoMinusesGiven)
 *
 * CLI_ShortOptionsNoValidation
 *
 * 1. + app_name -k         (OneShortKeyWithNoValue)
 * 2. + app_name -k4        (OneShortKeyWithNearNumberValue)
 * 3. + app_name -k 4       (OneShortKeyWithFarNumberValue)
 * 4. + app_name -k 4 3     (OneShortKeyWithTwoFarNumberValues)
 * 5. + app_name -k4 3      (OneShortKeyWithOneNearOneFarNumberValues)
 * 6. + app_name -k -j (TwoShortKeysWithTwoMinusesWithNoNumberValues)
 * 7. + app_name -kj (TwoShortKeysWithOneMinusWithNoNumberValues)
 * 8. + app_name -k1j2 (TwoShortKeysWithOneMinusAndTwoNearNumberValues)
 * 9. + app_name -k1 -j2 (TwoShortKeysWithTwoMinusesAndTwoNearNumberValues)
 * 10. + app_name -k 1 -j2
 * (TwoShortKeysWithTwoMinusesAndOneNearAndOneFarNumberValues)
 * 11. + app_name -k 1 -j 2 (TwoShortKeysWithTwoMinusesAndTwoFarNumberValues)
 * 12. - app_name -k1j
 * 13. - app_name -k value
 * 14. - app_name -k value1 value2
 * 15. - app_name -k value1 -j value2
 * 16. - app_name -k value -j
 * 17. - app_name -k v
 * 18. - app_name -k v
 * 19. - app_name -k v
 *
 * */

auto cli = CLI::CLI::get_instance();
std::list<CLI::CLI::token> expected_token_list;

void reset_all()
{
    expected_token_list.clear();
    cli->clear();
}

TEST(CLI_EmptyOptionsNoValidation, NoOptionsGiven)
{
    // Arrange
    reset_all();
    // In console: app_name
    const char* args_pack[] = {""};
    // expected_token_list is empty

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, OneMinusGiven)
{
    // Arrange
    reset_all();
    // In console: app_name -
    const char* args_pack[] = {"", "-"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_EmptyOptionsNoValidation, TwoMinusesGiven)
{
    // Arrange
    reset_all();
    // In console: app_name --
    const char* args_pack[] = {"", "--"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

/*******************************************************************************/

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWithNoValue)
{
    // Arrange
    reset_all();
    // In console: app_name -k
    const char* args_pack[] = {"", "-k"};
    expected_token_list = {{"k", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWithNearNumberValue)
{
    // Arrange
    reset_all();
    // In console: app_name -k4
    const char* args_pack[] = {"", "-k4"};
    expected_token_list = {{"k", "4"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWithFarNumberValue)
{
    // Arrange
    reset_all();
    // In console: app_name -k 4
    const char* args_pack[] = {"", "-k", "4"};
    expected_token_list = {{"k", "4"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWithTwoFarNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -k 4 3
    const char* args_pack[] = {"", "-k", "4", "3"};
    expected_token_list = {{"k", "4"}, {"k", "3"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWithOneNearOneFarNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -k4 3
    const char* args_pack[] = {"", "-k4", "3"};
    expected_token_list = {{"k", "4"}, {"k", "3"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation, TwoShortKeysWithTwoMinusesWithNoNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -k -j
    const char* args_pack[] = {"", "-k", "-j"};
    expected_token_list = {{"k", ""}, {"j", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation, TwoShortKeysWithOneMinusWithNoNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -kj
    const char* args_pack[] = {"", "-kj"};
    expected_token_list = {{"k", ""}, {"j", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysWithOneMinusAndTwoNearNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -kj
    const char* args_pack[] = {"", "-k1j2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysWithTwoMinusesAndTwoNearNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -k1 -j2
    const char* args_pack[] = {"", "-k1", "-j2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysWithTwoMinusesAndOneNearAndOneFarNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -k 1 -j2
    const char* args_pack[] = {"", "-k", "1", "-j2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysWithTwoMinusesAndTwoFarNumberValues)
{
    // Arrange
    reset_all();
    // In console: app_name -k 1 -j 2
    const char* args_pack[] = {"", "-k", "1", "-j", "2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

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
