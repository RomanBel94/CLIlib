#include "../CLIlib.h"

// has to be included after all other includes
#include "gtest/gtest.h"

/* TODO list:
 *
 * -----------------------------------------------
 * + Test_1:      Empty options with no validation
 * -----------------------------------------------
 *
 * + Case_1:      app_name
 *
 * + Case_2:      app_name -
 *
 * + Case_3:      app_name --
 *
 * + Case_4:      app_name - k
 *
 * + Case_5:      app_name -- k
 *
 * + Case_6:      app_name -k-
 *
 * + Case_7:      app_name k-
 *
 * + Case_8:      app_name ---
 *
 * -----------------------------------------------
 * + Test_2:      Short options with no validation
 * -----------------------------------------------
 *
 * + Case_1:      app_name -k
 *
 * + Case_2:      app_name -k4
 *
 * + Case_3:      app_name -k 4
 *
 * + Case_4:      app_name -k 4 3
 *
 * + Case_5:      app_name -k4 3
 *
 * + Case_6:      app_name -k -j
 *
 * + Case_7:      app_name -kj
 *
 * + Case_8:      app_name -k1j2
 *
 * + Case_9:      app_name -k1 -j2
 *
 * + Case_10:     app_name -k 1 -j2
 *
 * + Case_11:     app_name -k 1 -j 2
 *
 * + Case_12:     app_name -k1j
 *
 * + Case_13:     app_name -kj1
 *
 * + Case_14:     app_name -k value
 *
 * + Case_15:     app_name -k value1 value2
 *
 * + Case_16:     app_name -k value1 -j value2
 *
 * + Case_17:     app_name -k value -j
 *
 * + Case_18:     app_name -k v
 *
 * + Case_19:     app_name -key VA-lu-E
 *
 * + Case_20:     app_name -k-e-y
 *
 * + Case_21:     app_name just-a-value
 *
 * + Case_22:     app_name just-a-value1 justavalue2
 *
 * -----------------------------------------------
 * - Test_3:      Short options with no validation
 * -----------------------------------------------
 *
 * + Case_1:      app_name --long_option1
 *
 * + Case_2:      app_name --long_option1 value1
 *
 * + Case_3:      app_name --long_option1=value1
 *
 * - Case_4:      app_name
 *
 * - Case_5:      app_name
 *
 * - Case_6:      app_name
 *
 * - Case_7:      app_name
 *
 * - Case_8:      app_name
 *
 * - Case_9:      app_name
 *
 * - Case_10:     app_name
 *
 * - Case_11:     app_name
 *
 * - Case_12:     app_name
 *
 * - Case_13:     app_name
 *
 * - Case_14:     app_name
 *
 * - Case_15:     app_name
 *
 * - Case_16:     app_name
 *
 * - Case_17:     app_name
 *
 * - Case_18:     app_name
 *
 * - Case_19:     app_name
 *
 * - Case_20:     app_name
 *
 * - Case_21:     app_name
 *
 * - Case_22:     app_name
 *
 * */

auto cli = CLI::CLI::get_instance();
std::list<CLI::CLI::token> expected_token_list;

inline void reset_all()
{
    expected_token_list.clear();
    cli->clear();
}

TEST(Test_1, Case_1)
{
    // Arrange
    reset_all();
    // In terminal: app_name
    const char* args_pack[] = {""};
    // expected_token_list is empty

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_1, Case_2)
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

TEST(Test_1, Case_3)
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

TEST(Test_1, Case_4)
{
    // Arrange
    reset_all();
    // In terminal: app_name - k
    const char* args_pack[] = {"", "-", "k"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_1, Case_5)
{
    // Arrange
    reset_all();
    // In terminal: app_name -- k
    const char* args_pack[] = {"", "--", "k"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_1, Case_6)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k-
    const char* args_pack[] = {"", "-k-"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_1, Case_7)
{
    // Arrange
    reset_all();
    // In terminal: app_name k-
    const char* args_pack[] = {"", "k-"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_1, Case_8)
{
    // Arrange
    reset_all();
    // In terminal: app_name k-
    const char* args_pack[] = {"", "---"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

/*******************************************************************************/

TEST(Test_2, Case_1)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k
    const char* args_pack[] = {"", "-k"};
    expected_token_list = {{"k", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_2)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k4
    const char* args_pack[] = {"", "-k4"};
    expected_token_list = {{"k", "4"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_3)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k 4
    const char* args_pack[] = {"", "-k", "4"};
    expected_token_list = {{"k", "4"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_4)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k 4 3
    const char* args_pack[] = {"", "-k", "4", "3"};
    expected_token_list = {{"k", "4"}, {"k", "3"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_5)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k4 3
    const char* args_pack[] = {"", "-k4", "3"};
    expected_token_list = {{"k", "4"}, {"k", "3"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_6)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k -j
    const char* args_pack[] = {"", "-k", "-j"};
    expected_token_list = {{"k", ""}, {"j", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_7)
{
    // Arrange
    reset_all();
    // In terminal: app_name -kj
    const char* args_pack[] = {"", "-kj"};
    expected_token_list = {{"k", ""}, {"j", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_8)
{
    // Arrange
    reset_all();
    // In terminal: app_name -kj
    const char* args_pack[] = {"", "-k1j2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_9)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k1 -j2
    const char* args_pack[] = {"", "-k1", "-j2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_10)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k 1 -j2
    const char* args_pack[] = {"", "-k", "1", "-j2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_11)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k 1 -j 2
    const char* args_pack[] = {"", "-k", "1", "-j", "2"};
    expected_token_list = {{"k", "1"}, {"j", "2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_12)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k1j
    const char* args_pack[] = {"", "-k1j"};
    expected_token_list = {{"k", "1"}, {"j", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_13)
{
    // Arrange
    reset_all();
    // In terminal: app_name -kj1
    const char* args_pack[] = {"", "-kj1"};
    expected_token_list = {{"k", ""}, {"j", "1"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_14)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k value
    const char* args_pack[] = {"", "-k", "value"};
    expected_token_list = {{"k", "value"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_15)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k value1 value2
    const char* args_pack[] = {"", "-k", "value1", "value2"};
    expected_token_list = {{"k", "value1"}, {"k", "value2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_16)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k value1 value2
    const char* args_pack[] = {"", "-k", "value1", "-j", "value2"};
    expected_token_list = {{"k", "value1"}, {"j", "value2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_17)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k value1 value2
    const char* args_pack[] = {"", "-k", "value1", "-j"};
    expected_token_list = {{"k", "value1"}, {"j", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_18)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k v
    const char* args_pack[] = {"", "-k", "v"};
    expected_token_list = {{"k", "v"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_19)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k v
    const char* args_pack[] = {"", "-key", "VA-lu-E"};
    expected_token_list = {{"k", ""}, {"e", ""}, {"y", "VA-lu-E"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_20)
{
    // Arrange
    reset_all();
    // In terminal: app_name -k-e-y
    const char* args_pack[] = {"", "-k-e-y"};
    // expected_token_list is empty

    // Act
    EXPECT_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                 const_cast<char**>(args_pack)),
                 CLI::cli_parsing_error);

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_21)
{
    // Arrange
    reset_all();
    // In terminal: app_name just-a-value
    const char* args_pack[] = {"", "just-a-value"};
    expected_token_list = {{"", "just-a-value"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_2, Case_22)
{
    // Arrange
    reset_all();
    // In terminal: app_name just-a-value1 justavalue2
    const char* args_pack[] = {"", "just-a-value1", "justavalue2"};
    expected_token_list = {{"", "just-a-value1"}, {"", "justavalue2"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_3, Case_1)
{
    // Arrange
    reset_all();
    // In terminal: app_name --long_option1
    const char* args_pack[] = {"", "--long_option1"};
    expected_token_list = {{"long_option1", ""}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_3, Case_2)
{
    // Arrange
    reset_all();
    // In terminal: app_name --long_option1 value1
    const char* args_pack[] = {"", "--long_option1", "value1"};
    expected_token_list = {{"long_option1", "value1"}};

    // Act
    EXPECT_NO_THROW(cli->parse_args(sizeof(args_pack) / sizeof(*args_pack),
                                    const_cast<char**>(args_pack)));

    // Assert
    EXPECT_EQ(cli->tokens(), expected_token_list);
}

TEST(Test_3, Case_3)
{
    // Arrange
    reset_all();
    // In terminal: app_name --long_option1=value1
    const char* args_pack[] = {"", "--long_option1=value1"};
    expected_token_list = {{"long_option1", "value1"}};

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
