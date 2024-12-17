#include "CLIlib.h"

int main(int argc, char** argv)
{
	CLI::CLI cli(argc, argv);
	cli.add_option("main");
	cli.parse_arguments();

	for (const auto& token : cli.tokens())
		std::cout << token.first << " " << token.second << std::endl;

	return 0;
}
