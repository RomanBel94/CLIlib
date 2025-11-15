#include "CLIlib.h"

#ifdef NDEBUG
#define LOG(message)
#define ERR(message)
#define DEB(message)
#else
#include <iostream>
#define LOG(message)                                                           \
    std::clog << "[LOG]: " << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": "  \
              << #message << '\n';
#define ERR(message)                                                           \
    std::clog << "[ERR]: " << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": "  \
              << #message << '\n';
#define DEB(message)                                                           \
    std::clog << "[DEB]: " << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": "  \
              << #message << '\n';
#endif

namespace CLI
{
void CLI::parse_args(int argc, char** argv)
{
    for (int i{1}; i < argc; ++i)
    {
        std::string arg{argv[i]};
        // parameter is short
        if (arg[0] == '-' && std::isalpha(arg[1]))
            _extract_short_opts(&arg[1]);
        // parameter is long
        else if (arg.substr(0, 2) == "--" && std::isalpha(arg[2]) &&
                 arg.size() > 3)
            _extract_long_opt(&arg[2]);
        // parsing value
        else
        {
            if (!_tokens.empty() && _tokens.back().second.empty())
                // add value to existing token if
                // it doesn't have value
                _tokens.back().second = arg;
            else // add new token with the same key as last and a new value
            {
                _current_value = arg;
                _append_token();
            }
        }
    }
}

void CLI::_extract_short_opts(const char* opt)
{
    while (*opt)
    {
        _current_option = *opt++;
        _current_value.clear();

        // for token which looks like -p777
        while (isdigit(*opt))
            _current_value.push_back(*opt++);

        _append_token();
    }
    _last_option_read = OptionType::short_option;
}

void CLI::_extract_long_opt(const char* opt)
{
    _current_option.clear();
    _current_value.clear();

    // for token which looks like --param=value
    while (*opt && *opt != '=')
        _current_option.push_back(*opt++);

    if (*opt++ == '=')
        _current_value = opt;

    _append_token();

    _last_option_read = OptionType::long_option;
}

void CLI::_append_token()
{
    // this token is not expected
    if (_valid_parameters.find(_current_option) == _valid_parameters.end())
        _throw_exception("Invalid option: " + _current_option);

    // if token is expected
    _tokens.emplace_back(_current_option, _current_value);
}

void CLI::_throw_exception(const std::string& msg)
{
    clear();
    throw cli_parsing_error{msg};
}

void CLI::add_long_option(const _option& long_opt)
{
    _valid_parameters.emplace(long_opt);
}

void CLI::add_long_option(const _option&& long_opt)
{
    _valid_parameters.emplace(std::move(long_opt));
}

void CLI::add_short_option(char opt) { _valid_parameters.emplace(1, opt); }

} // namespace CLI
