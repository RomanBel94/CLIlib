#include <iostream>
#include "CLIlib.h"

int main(int argc, char** argv)
{
	auto& cli = CLI::CLI::get_instance();

    cli->add_short_opts('t', 'e', 's', 't');
    cli->add_long_opts("test", "cpp", "your_mother");

    cli->parse_args(argc, argv);

	for (const auto& token : cli->tokens())
		std::cout << token.key << " " << token.value << std::endl;

	return 0;
}
