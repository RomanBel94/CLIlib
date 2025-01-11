#include "CLIlib.h"
#include <cassert>
#include <iostream>
#include <list>

int main(int argc, char** argv)
{
    size_t current_test{0};
    auto cli = CLI::CLI::get_instance();

    // test #1
    int args_c = 6;
    const char* args_v[] = {"", "-t12", "-e12s", "43", "param", "-r"};
    cli->parse_args(args_c, const_cast<char**>(args_v));
    std::list<CLI::CLI::token> answer{
        {"t", "12"}, {"e", "12"}, {"s", "43"}, {"s", "param"}, {"r", ""}};

    if (cli->tokens() == answer)
        std::cout << "Test #" << ++current_test << " passed!" << std::endl;
    else
        std::cout << "Test #" << ++current_test << " failed!" << std::endl;

    cli->clear();

    // for (const auto& [key, value] : cli->tokens())
    //     std::cout << key << " " << value << std::endl;

    return 0;
}
