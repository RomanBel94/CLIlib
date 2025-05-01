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
 * 1. + app_name -k         (OneShortKeyWasGivenWithNoValue)
 * 2. + app_name -k4        (OneShortKeyWasGivenWithNearNumberValue)
 * 3. + app_name -k 4       (OneShortKeyWasGivenWithFarNumberValue)
 * 4. + app_name -k 4 3     (OneShortKeyWasGivenWithTwoFarNumberValues)
 * 5. + app_name -k4 3      (OneShortKeyWasGivenWithOneNearOneFarNumberValues)
 * 6. + app_name -k -j (TwoShortKeysWithTwoMinusesWasGivenWithNoNumberValues)
 * 7. + app_name -kj (TwoShortKeysWithOneMinusWasGivenWithNoNumberValues)
 * 8. + app_name -k1j2 (TwoShortKeysWithOneMinusWasGivenAndTwoNumberValues)
 * 9. + app_name -k1 -j2 (TwoShortKeysWithTwoMinusesWasGivenAndTwoNumberValues)
 * 10. - app_name -k 1 -j2
 * 11. - app_name -k 1 -j 2
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWasGivenWithNoValue)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWasGivenWithNearNumberValue)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWasGivenWithFarNumberValue)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyWasGivenWithTwoFarNumberValues)
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

TEST(CLI_ShortOptionsNoValidation,
     OneShortKeyWasGivenWithOneNearOneFarNumberValues)
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

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysWithTwoMinusesWasGivenWithNoNumberValues)
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

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysWithOneMinusWasGivenWithNoNumberValues)
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
     TwoShortKeysWithOneMinusWasGivenAndTwoNumberValues)
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
     TwoShortKeysWithTwoMinusesWasGivenAndTwoNumberValues)
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

int main(int argc, char** argv)
{
    // inits googletest framework
    testing::InitGoogleTest(&argc, argv);

    // runs all tests
    return RUN_ALL_TESTS();
}
