#include "CLIlib.h"
#include <iostream>

int main(int argc, char** argv)
{
    auto& cli = CLI::CLI::get_instance();

    cli->add_opt('t', 'e', 's', 't');
    cli->add_long_opt("test");
    cli->parse_args(argc, argv);

    for (const auto& [key, value] : cli->tokens())
        std::cout << key << " " << value << std::endl;

    return 0;
}
