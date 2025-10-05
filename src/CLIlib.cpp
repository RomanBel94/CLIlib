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

    if (*opt++ == '=')
        _current_value = opt;

    _append_token();
}

void CLI::_append_token()
{
    // this token is not expected
    if (!_is_valid_token(_current_param))
        _throw_exception("Invalid option: " + _current_param);

    // if token is expected
    _tokens.emplace_back(_current_param, _current_value);
}

void CLI::_throw_exception(const std::string& msg)
{
    clear();
    throw cli_parsing_error{msg};
}

bool CLI::_is_valid_token(const _Param& opt) const noexcept
{
    return _valid_parameters.find(opt) != _valid_parameters.end();
}

void CLI::_add_long_opt(const _Param& long_opt)
{
    _valid_parameters.emplace(long_opt);
}

void CLI::_add_long_opt(const std::initializer_list<_Param>&& opt_list)
{
    for (const auto& opt : opt_list)
        _add_long_opt(opt);
}

void CLI::_add_opt(char opt) { _valid_parameters.emplace(1, opt); }

void CLI::_add_opt(const std::initializer_list<char>&& opt_list)
{
    for (auto opt : opt_list)
        _add_opt(opt);
}

void CLI::_add_opt(const _Param& opts)
{
    if (opts.empty())
    {
        _valid_parameters.emplace(opts);
        return;
    }

    for (auto opt : opts)
        _add_opt(opt);
}
} // namespace CLI
