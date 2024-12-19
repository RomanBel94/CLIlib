#include <iostream>
#include "CLIlib.h"

int main(int argc, char** argv)
{
	auto cli = CLI::CLI::get_instance();
	cli->add_option("a");
	cli->add_option("f");
	cli->parse_arguments(argc, argv);

	for (const auto& token : cli->tokens())
		std::cout << token.first << " " << token.second << std::endl;

	return 0;
}
