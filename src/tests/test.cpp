#include "../CLIlib.h"

// has to be included after all other includes
#include "../../googletest/googletest/include/gtest/gtest.h"

/* TODO list:
 *
 * CLI_EmptyOptionsNoValidation
 *
 * 1. + app_name            (NoOptions)
 *
 * 2. + app_name -          (OneMinus)
 *
 * 3. + app_name --         (TwoMinuses)
 *
 * CLI_ShortOptionsNoValidation
 *
 * 1. + app_name -k         (OneShortKeyNoValue)
 *
 * 2. + app_name -k4        (OneShortKeyNearNumberValue)
 *
 * 3. + app_name -k 4       (OneShortKeyFarNumberValue)
 *
 * 4. + app_name -k 4 3     (OneShortKeyTwoFarNumberValues)
 *
 * 5. + app_name -k4 3      (OneShortKeyOneNearOneFarNumberValues)
 *
 * 6. + app_name -k -j (TwoShortKeysTwoMinusesWithNoNumberValues)
 *
 * 7. + app_name -kj (TwoShortKeysOneMinusWithNoNumberValues)
 *
 * 8. + app_name -k1j2 (TwoShortKeysOneMinusTwoNearNumberValues)
 *
 * 9. + app_name -k1 -j2 (TwoShortKeysTwoMinusesTwoNearNumberValues)
 *
 * 10. + app_name -k 1 -j2
 * (TwoShortKeysTwoMinusesOneNearAndOneFarNumberValues)
 *
 * 11. + app_name -k 1 -j 2 (TwoShortKeysTwoMinusesTwoFarNumberValues)
 *
 * 12. + app_name -k1j (TwoShortKeysOneMinusOneNearNumberValueAfterFirst)
 *
 * 13. + app_name -kj1
 * (TwoShortKeysOneMinusOneNearNumberValueAfterSecond)
 *
 * 14. - app_name -k value
 *
 * 15. - app_name -k value1 value2
 *
 * 16. - app_name -k value1 -j value2
 *
 * 17. - app_name -k value -j
 *
 * 18. - app_name -k
 *
 * 19. - app_name -k v
 *
 * 20. - app_name -k v
 *
 * */

auto cli = CLI::CLI::get_instance();
std::list<CLI::CLI::token> expected_token_list;

void reset_all()
{
    expected_token_list.clear();
    cli->clear();
}

TEST(CLI_EmptyOptionsNoValidation, NoOptions)
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

TEST(CLI_EmptyOptionsNoValidation, OneMinus)
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

TEST(CLI_EmptyOptionsNoValidation, TwoMinuses)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyNoValue)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyNearNumberValue)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyFarNumberValue)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyTwoFarNumberValues)
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

TEST(CLI_ShortOptionsNoValidation, OneShortKeyOneNearOneFarNumberValues)
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

TEST(CLI_ShortOptionsNoValidation, TwoShortKeysTwoMinusesWithNoNumberValues)
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

TEST(CLI_ShortOptionsNoValidation, TwoShortKeysOneMinusWithNoNumberValues)
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

TEST(CLI_ShortOptionsNoValidation, TwoShortKeysOneMinusTwoNearNumberValues)
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

TEST(CLI_ShortOptionsNoValidation, TwoShortKeysTwoMinusesTwoNearNumberValues)
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
     TwoShortKeysTwoMinusesOneNearAndOneFarNumberValues)
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

TEST(CLI_ShortOptionsNoValidation, TwoShortKeysTwoMinusesTwoFarNumberValues)
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

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysOneMinusOneNearNumberValueAfterFirst)
{
    // Arrange
    reset_all();
    // In console: app_name -k1j
    const char* args_pack[] = {"", "-k1j"};
    expected_token_list = {{"k", "1"}, {"j", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(CLI_ShortOptionsNoValidation,
     TwoShortKeysOneMinusOneNearNumberValueAfterSecond)
{
    // Arrange
    reset_all();
    // In console: app_name -kj1
    const char* args_pack[] = {"", "-kj1"};
    expected_token_list = {{"k", ""}, {"j", "1"}};

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
