#include "CLIlib.h"

namespace CLI
{
	void CLI::parse_arguments()
	{
		_current_param = "main";
		_current_value = argv[0];

		if (_is_valid(_current_param))
			_tokens.emplace_back(_current_param, _current_value);
		else
			throw CLI_parsing_error("ERROR: Invalid argument");

		for (int i = 1; i < argc; ++i) {}
	}

	bool CLI::_is_valid(const std::string& argument) const noexcept
	{
		return _valid_parameters.find(argument) != _valid_parameters.end();
	}
}
