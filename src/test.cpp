#include <iostream>
#include "CLIlib.h"

int main(int argc, char** argv)
{
	auto& cli = CLI::CLI::get_instance();

    cli->parse_args(argc, argv);

	for (const auto& token : cli->tokens())
		std::cout << token.key << " " << token.value << std::endl;

	return 0;
}
