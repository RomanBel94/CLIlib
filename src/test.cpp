#include <iostream>
#include "CLIlib.h"

int main(int argc, char** argv)
{
	auto& cli = CLI::CLI::get_instance();

	try
	{
		cli->parse_args(argc, argv);
	}
	catch (const CLI::cli_parsing_error& er)
	{
		std::cout << er.what() << std::endl;
		return -1;
	}

	for (const auto& token : cli->tokens())
		std::cout << token.first << " " << token.second << std::endl;

	return 0;
}
