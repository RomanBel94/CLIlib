#include "CLIlib.h"

namespace CLI
{
	void CLI::parse_arguments(int argc, char** argv)
	{
		// bush back first token (argv[0])
		_current_value = argv[0];
		_append_param();

		for (int i{ 1 }; i < argc; ++i)
		{
			if (argv[i][0] == '-' && argv[i][1] == '-');
			else if (argv[i][0] == '-' && argv[i][1]) _extract_keys(argv[i] + 1);
			else _tokens.back().second = argv[i];
		}
	}

	std::shared_ptr<::CLI::CLI>& CLI::get_instance()
	{
		static std::shared_ptr<::CLI::CLI> ptr{ new ::CLI::CLI };
		return ptr;
	}

	void CLI::_extract_keys(const char* keys)
	{
		while (*keys)
		{
			_current_param = *(keys++);
			_current_value = "0";
			while (isdigit(*keys))
			{
				_current_value = "";
				_current_value += *(keys++);
			}
			_append_param();
		}
	}

	void CLI::_append_param()
	{
		_validate_current_arg();
		_tokens.emplace_back(_current_param, _current_value);
	}

	void CLI::_validate_current_arg() const
	{
		if (_valid_parameters.find(_current_param) == _valid_parameters.end())
			throw CLI_parsing_error("ERROR: Invalid argument");
	}
}
