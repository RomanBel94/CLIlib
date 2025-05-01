#include "CLIlib.h"

namespace CLI
{
const std::shared_ptr<CLI>& CLI::get_instance()
{
    static const std::shared_ptr<CLI> ptr{new CLI()};
    return ptr;
}

void CLI::parse_args(int argc, char** argv)
{
    for (int i{1}; i < argc; ++i)
    {
        // parsing parameter
        if (argv[i][0] == '-')
            // parameter is long
            if (argv[i][1] == '-')
                _extract_long_opt(argv[i] + 2);
            // parameter is short
            else
                _extract_short_opt(argv[i] + 1);
        // parsing value
        else
        {
            if (_tokens.back().second.empty()) // add value to existing token if
                                               // it doesn't have value
                _tokens.back().second = argv[i];
            else // add new token with the same key as last and a new value
            {
                _current_value = argv[i];
                _append_token();
            }
        }
    }
}

void CLI::_extract_short_opt(const char* opt)
{
    _check_empty_option(opt);
    while (*opt)
    {
        _current_param = *opt++;
        _current_value.clear();

        // for token which looks like -p777
        while (isdigit(*opt))
            _current_value.push_back(*opt++);
        _append_token();
    }
}

void CLI::_extract_long_opt(const char* opt)
{
    _check_empty_option(opt);
    _current_param.clear();
    _current_value.clear();

    // for token which looks like --param=value
    while (*opt && *opt != '=')
        _current_param.push_back(*opt++);
    if (*opt == '=')
    {
        ++opt;
        _current_value = opt;
    }
    if (_current_param.size() == 1) // expected long option, short was given
    {
        std::string wrong_option{_current_param};
        clear();
        throw(cli_parsing_error("ERROR: Expected long option. " + wrong_option +
                                " was given."));
    }

    _append_token();
}

void CLI::_append_token()
{
    _validate_current_arg();
    _tokens.emplace_back(_current_param, _current_value);
}

void CLI::_validate_current_arg()
{
    // this token is not expected
    if (!_valid_parameters.empty() && !_is_valid_token(_current_param))
    {
        std::string wrong_option{_current_param};
        clear();
        throw cli_parsing_error("ERROR: Invalid option: " + wrong_option);
    }
}

void CLI::_check_empty_option(const char* opt)
{
    if (!(*opt))
    {
        clear();
        throw cli_parsing_error("ERROR: Empty option");
    }
}

bool CLI::_is_valid_token(const _Param& opt) const noexcept
{
    return _valid_parameters.find(opt) != _valid_parameters.end();
}

void CLI::_add_long_opt(const std::initializer_list<_Param>&& opt_list)
{
    for (const auto& opt : opt_list)
        add_long_opt(opt);
}

void CLI::_add_opt(char opt) { _valid_parameters.emplace(1, opt); }

void CLI::_add_opt(const std::initializer_list<char>&& opt_list)
{
    for (auto opt : opt_list)
        _add_opt(opt);
}

void CLI::_add_opt(const _Param&& opts)
{
    for (auto opt : opts)
        _add_opt(opt);
}
} // namespace CLI
