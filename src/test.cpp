#include "CLIlib.h"
#include <iostream>

int main(int argc, char** argv)
{
    auto& cli = CLI::CLI::get_instance();

    cli->parse_args(argc, argv);

    for (const auto& [key, value] : cli->tokens())
        std::cout << key << " " << value << std::endl;

    return 0;
}
