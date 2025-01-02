#include "CLIlib.h"
#include <iostream>

int main(int argc, char** argv)
{
    auto& cli = CLI::CLI::get_instance();

    cli->add_opt('t');
    cli->add_opt('t', 'e', 's', 't');
    cli->add_opt("test");

    cli->add_long_opt("test", "test2");
    cli->add_long_opt("cpp");
    cli->add_long_opt("your_mother");

    cli->parse_args(argc, argv);

    for (const auto& [key, value] : cli->tokens())
        std::cout << key << " " << value << std::endl;

    return 0;
}
