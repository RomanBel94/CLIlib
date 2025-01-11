#include "CLIlib.h"
#include <cassert>
#include <iostream>
#include <list>

int main(int argc, char** argv)
{
    size_t current_test{0};
    auto cli = CLI::CLI::get_instance();

    // test #1
    int argc1 = 1;
    const char* argv1[] = {""};
    cli->parse_args(argc1, const_cast<char**>(argv1));
    std::list<CLI::CLI::token> answer1;

    if (cli->tokens() == answer1)
        std::cout << "Test #" << ++current_test << " passed!" << std::endl;
    else
    {
        std::cout << "Test #" << ++current_test << " failed!" << std::endl;
        std::cout << "Given args:\n";
        for (int i{1}; i < argc1; ++i)
            std::cout << argv1[i] << '\n';
        std::cout << "Expected:\n";
        for (auto [opt, value] : answer1)
            std::cout << opt << ' ' << value << '\n';
        std::cout << "Collected:\n";
        for (auto [opt, value] : cli->tokens())
            std::cout << opt << ' ' << value << '\n';
        std::cout << std::endl;
    }

    cli->clear();

    // test #2
    int argc2 = 6;
    const char* argv2[] = {"", "-t12", "-e12s", "43", "param", "-r"};
    cli->parse_args(argc2, const_cast<char**>(argv2));
    std::list<CLI::CLI::token> answer2{
        {"t", "12"}, {"e", "12"}, {"s", "43"}, {"s", "param"}, {"r", ""}};

    if (cli->tokens() == answer2)
        std::cout << "Test #" << ++current_test << " passed!" << std::endl;
    else
    {
        std::cout << "Test #" << ++current_test << " failed!" << std::endl;
        std::cout << "Given args:\n";
        for (int i{1}; i < argc2; ++i)
            std::cout << argv2[i] << '\n';
        std::cout << "Expected:\n";
        for (auto [opt, value] : answer2)
            std::cout << opt << ' ' << value << '\n';
        std::cout << "Collected:\n";
        for (auto [opt, value] : cli->tokens())
            std::cout << opt << ' ' << value << '\n';
        std::cout << std::endl;
    }

    cli->clear();

    // test #3
    int argc3 = 3;
    const char* argv3[] = {"", "param1", "param2"};
    cli->parse_args(argc3, const_cast<char**>(argv3));
    std::list<CLI::CLI::token> answer3{{"", "param1"}, {"", "param2"}};

    if (cli->tokens() == answer3)
        std::cout << "Test #" << ++current_test << " passed!" << std::endl;
    else
    {
        std::cout << "Test #" << ++current_test << " failed!" << std::endl;
        std::cout << "Given args:\n";
        for (int i{1}; i < argc3; ++i)
            std::cout << argv3[i] << '\n';
        std::cout << "Expected:\n";
        for (auto [opt, value] : answer3)
            std::cout << opt << ' ' << value << '\n';
        std::cout << "Collected:\n";
        for (auto [opt, value] : cli->tokens())
            std::cout << opt << ' ' << value << '\n';
        std::cout << std::endl;
    }

    cli->clear();

    // test #4
    int argc4 = 3;
    const char* argv4[] = {"", "param1", "param2"};
    bool exception_catched{false};
    cli->add_long_opt("param1", "param3");
    try
    {
        cli->parse_args(argc4, const_cast<char**>(argv4));
    }
    catch (const CLI::cli_parsing_error& ex)
    {
        exception_catched = true;
    }

    if (exception_catched)
        std::cout << "Test #" << ++current_test << " passed!" << std::endl;
    else
    {
        std::cout << "Test #" << ++current_test << " failed!" << std::endl;
        std::cout << "No exception catched" << std::endl;
        std::cout << std::endl;
    }

    cli->clear();

    // test #5
    int argc5 = 3;
    const char* argv5[] = {"", "param1", "--"};
    exception_catched = false;
    cli->add_long_opt("param1", "param3");
    try
    {
        cli->parse_args(argc5, const_cast<char**>(argv5));
    }
    catch (const CLI::cli_parsing_error& ex)
    {
        exception_catched = true;
    }

    if (exception_catched)
        std::cout << "Test #" << ++current_test << " passed!" << std::endl;
    else
    {
        std::cout << "Test #" << ++current_test << " failed!" << std::endl;
        std::cout << "No exception catched" << std::endl;
        std::cout << std::endl;
    }

    cli->clear();

    // test #6
    int argc6 = 2;
    const char* argv6[] = {"", "-"};
    exception_catched = false;
    try
    {
        cli->parse_args(argc6, const_cast<char**>(argv6));
    }
    catch (const CLI::cli_parsing_error& ex)
    {
        exception_catched = true;
    }

    if (exception_catched)
        std::cout << "Test #" << ++current_test << " passed!" << std::endl;
    else
    {
        std::cout << "Test #" << ++current_test << " failed!" << std::endl;
        std::cout << "No exception catched" << std::endl;
        std::cout << std::endl;
    }

    cli->clear();
    // for (const auto& [key, value] : cli->tokens())
    //     std::cout << key << " " << value << std::endl;

    return 0;
}
