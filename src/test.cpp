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

    // for (const auto& [key, value] : cli->tokens())
    //     std::cout << key << " " << value << std::endl;

    return 0;
}
