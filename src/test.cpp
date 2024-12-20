#include <iostream>
#include "CLIlib.h"

int main(int argc, char** argv)
{
	auto& cli = CLI::CLI::get_instance();
	cli->add_short_opt('a');
	cli->add_short_opt('f');
	cli->add_short_opts({ "ds", "bn" });
	cli->add_short_opts({ 'z', 'x'});
	cli->add_short_opts("qwerty");
	cli->add_long_opt("test");

	try
	{
		cli->parse_args(argc, argv);
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
