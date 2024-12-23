#include "CLIlib.h"

namespace CLI
{
    const std::shared_ptr<CLI>& CLI::get_instance()
    {
        static const std::shared_ptr<CLI> ptr { new CLI() };
        return ptr;
    }

	void CLI::add_opt(const char opt)
	{
		_valid_parameters.emplace(1, opt);
	}

	void CLI::add_opt(const _Param& opts)
	{
		for (const auto opt : opts)
			add_opt(opt);
	}

	void CLI::add_opt(const std::initializer_list<_Param>& list)
	{
		for (const auto& param : list)
			add_opt(param);
	}

	void CLI::add_opt(const std::initializer_list<char>& list)
	{
		for (const auto opt : list)
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

    bool CLI::is_valid_token(const token& token) const noexcept
    {
        return is_valid_token(token.first);
    }

    bool CLI::is_valid_token(const _Param& opt) const noexcept
    {
        return _valid_parameters.find(opt) != _valid_parameters.cend() || opt.empty();
    }

	void CLI::parse_args(int argc, char** argv)
	{
        _tokens.emplace_back("", argv[0]);

		for (int i{ 1 }; i < argc; ++i)
		{
            // parsing parameter
            if (argv[i][0] == '-')
			{
                if (argv[i][1] == '-')                      // parameter is long
                    _extract_long_opt(argv[i] + 2);
                else                                        // parameter is short
                    _extract_short_opts(argv[i] + 1);
			} 
            // parsing value
            else
			{
                if (_tokens.back().second.empty())  // add value to existing token if it doesn't have value
                {
                    _tokens.back().second = argv[i];
                }
                else                                // add new token with same key as last and a new value
                {                
			        _current_value = argv[i];
				    if (_tokens.back().first.empty()) // situation when value was given as first argument
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
        if (!(*opt)) throw cli_parsing_error("ERROR: Empty option");
    }

	void CLI::_extract_short_opts(const char* opt)
	{
        _check_empty_option(opt);
		while (*opt)
		{
			_current_param = *opt++;
		    _current_value.clear();
			while (isdigit(*opt))
			{
				_current_value.push_back(*opt++);
			}
			_append_token();
		}
	}

	void CLI::_extract_long_opt(const char* opt)
	{
        _check_empty_option(opt);
		_current_param.clear();
		_current_value.clear();
		while (*opt && *opt != '=')
		{
			_current_param.push_back(*opt++);
		}
		if (*opt == '=')
		{
			++opt;
			_current_value = opt;
		}
        if (_current_param.size() == 1) // expected long option, short was given
            throw (cli_parsing_error("ERROR: Expected long option"));
		_append_token();
	}

	void CLI::_append_token()
	{
		_validate_current_arg();
		_tokens.emplace_back(_current_param, _current_value);
	}

	void CLI::_validate_current_arg() const
	{
        // this token is not expected
		if (_valid_parameters.find(_current_param) == _valid_parameters.end())
			throw cli_parsing_error("ERROR: Invalid argument: " + _current_param);
	}
}
