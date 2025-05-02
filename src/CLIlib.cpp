#include "CLIlib.h"
#include <regex>

namespace CLI
{
const std::shared_ptr<CLI>& CLI::get_instance()
{
    static const std::shared_ptr<CLI> ptr{new CLI()};
    return ptr;
}

void CLI::parse_args(int argc, char** argv)
{
    std::regex short_option_pattern{R"(-([A-Z|a-z]+\d*)+)"};
    std::regex long_option_pattern{R"(--[A-Z|a-z]\w+(-\w+)*(=\w+(-\w+)*)?)"};
    std::regex value_pattern{R"([A-Z|a-z|\d]\w*(-[A-Z|a-z|\d]\w*)*)"};

    for (int i{1}; i < argc; ++i)
    {
        // parameter is short
        if (std::regex_match(argv[i], short_option_pattern))
            _extract_short_opts(argv[i] + 1);
        // parameter is long
        else if (std::regex_match(argv[i], long_option_pattern))
            _extract_long_opt(argv[i] + 2);
        // parsing value
        else if (std::regex_match(argv[i], value_pattern))
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
        else
            throw cli_parsing_error{"Invalid argument: " +
                                    std::string(argv[i])};
    }
}

void CLI::_extract_short_opts(const char* opt)
{
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

    _append_token();
}

void CLI::_append_token()
{
    // this token is not expected
    if (!_valid_parameters.empty() && !_is_valid_token(_current_param))
    {
        std::string wrong_option{_current_param};
        clear();
        throw cli_parsing_error("ERROR: Invalid option: " + wrong_option);
    }
    // if token is expected or valid parameters list is empty
    _tokens.emplace_back(_current_param, _current_value);
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
