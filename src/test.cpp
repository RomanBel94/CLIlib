#include <iostream>
#include "CLIlib.h"

int main(int argc, char** argv)
{
	auto cli = CLI::CLI::get_instance();
	cli->add_option("a");
	cli->add_option("f");
	cli->add_options({ "d", "s" });
	cli->add_options("qwerty");

	try
	{
		cli->parse_arguments(argc, argv);
	}
	catch (const CLI::cli_parsing_error& er)
	{
		std::cout << er.what() << std::endl;
		exit(-1);
	}

	for (const auto& token : cli->tokens())
		std::cout << token.first << " " << token.second << std::endl;

	return 0;
}
