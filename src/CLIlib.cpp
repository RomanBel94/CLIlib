﻿#include "CLIlib.h"

namespace CLI
{
    std::shared_ptr<CLI>& CLI::get_instance()
    {
        static std::shared_ptr<CLI> ptr { new CLI() };
        return ptr;
    }

	void CLI::add_opt(const char opt)
	{
		_valid_parameters.emplace(1, opt);
	}

	void CLI::add_opt(const _Param& opts)
	{
		for (auto opt : opts)
			add_opt(opt);
	}

	void CLI::add_opt(const std::initializer_list<_Param>& list)
	{
		for (const auto& param : list)
			add_opt(param);
	}

	void CLI::add_opt(const std::initializer_list<char>& list)
	{
		for (auto opt : list)
			add_opt(opt);
	}

	void CLI::add_long_opt(const _Param& opt)
	{
		_valid_parameters.emplace(opt);
	}

    void CLI::add_long_opt(const std::initializer_list<_Param>& list)
    {
        for (const auto& opt : list)
            add_long_opt(opt);
    }

	void CLI::parse_args(int argc, char** argv)
	{
        _current_value = argv[0];
        _append_token();

		for (int i{ 1 }; i < argc; ++i)
		{
            if (argv[i][0] == DIVIDER)
			{
                if (argv[i][1] == DIVIDER)
                    _extract_long_opt(argv[i] + 2);
                else
                    _extract_short_opts(argv[i] + 1);
			} 
            else
			{
                if (_tokens.back().value == EMPTY)
                {
                    _tokens.back().value = argv[i];
                }
                else 
                {                
			        _current_value = argv[i];
				    if (_tokens.back().key == EMPTY)
                        throw cli_parsing_error("ERROR: Unexpected value: " + _current_value);
			        _append_token();
                }
			}
		}
	}

	void CLI::clear()
	{
		_tokens.clear();
		_valid_parameters.clear();
	}

    void CLI::_check_empty_option(const char* opt)
    {
        if (!(*opt)) throw cli_parsing_error("ERROR: Empty option.");
    }

	void CLI::_extract_short_opts(const char* opt)
	{
        _check_empty_option(opt);
		while (*opt)
		{
			_current_param = *opt++;
		    _current_value = EMPTY;
			while (isdigit(*opt))
			{
				_current_value += *opt++;
			}
			_append_token();
		}
	}

	void CLI::_extract_long_opt(const char* opt)
	{
        _check_empty_option(opt);
		_current_param = EMPTY;
		_current_value = EMPTY;
		while (*opt && *opt != '=')
		{
			_current_param += *opt++;
		}
		if (*opt == '=')
		{
			++opt;
			_current_value = opt;
		}
		_append_token();
	}

	void CLI::_append_token()
	{
		_validate_current_arg();
		_tokens.emplace_back(_current_param, _current_value);
	}

	void CLI::_validate_current_arg() const
	{
		if (_valid_parameters.find(_current_param) == _valid_parameters.end())
			throw cli_parsing_error("ERROR: Invalid argument: " + _current_param);
	}
}
