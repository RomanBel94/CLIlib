#include "CLIlib.h"

namespace CLI
{
	void CLI::add_options(const std::initializer_list<_Param>& list)
	{
		for (const auto& key : list)
			_valid_parameters.emplace(key);
	}

	void CLI::add_options(const _Param& params)
	{
		for (auto key : params)
			_valid_parameters.emplace(_Param(1, key));
	}

	void CLI::parse_arguments(int argc, char** argv)
	{
		// bush back first token (argv[0])
		_tokens.emplace_back(argv[0], argv[0]);

		for (int i{ 1 }; i < argc; ++i)
		{
			if (argv[i][0] == '-' && argv[i][1] == '-')
			{
				;
			}
			else if (argv[i][0] == '-' && argv[i][1])
			{
				_extract_keys(argv[i] + 1);
			}
			else 
			{
				if (_tokens.back().second != "")
				{
					_current_value = argv[i];
					_append_token();
				}
				else
				{
					_tokens.back().second = argv[i];
				}
			}
		}
	}

	std::shared_ptr<::CLI::CLI>& CLI::get_instance() noexcept
	{
		static std::shared_ptr<::CLI::CLI> ptr{ new ::CLI::CLI() };
		return ptr;
	}

	void CLI::_extract_keys(const char* keys)
	{
		while (*keys)
		{
			_current_param = *(keys++);
		    _current_value = "";
			while (isdigit(*keys))
			{
				_current_value += *(keys++);
			}
			_append_token();
		}
	}

	void CLI::_append_token()
	{
		_validate_current_arg();
		_tokens.emplace_back(_current_param, _current_value);
	}

	void CLI::_validate_current_arg() const
	{
		if (_valid_parameters.find(_current_param) == _valid_parameters.end())
			throw cli_parsing_error("ERROR: Invalid argument " + _current_param);
	}
}
