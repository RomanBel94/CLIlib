#pragma once
#ifndef CLI_LIB_H

#include <list>
#include <stdexcept>
#include <unordered_set>

namespace CLI
{
class CLI final
{
public:
    // Type aliases
    using _option = std::string;
    using _value = std::string;
    using token = std::pair<_option, _value>;

    // Overloaded functions for adding new options to be valid
    void add_short_option(char opt);
    void add_long_option(const _option& long_opt);
    void add_long_option(const _option&& long_opt);

    // Parse command-line arguments and place them into std::list of tokens
    void parse_args(int argc, char** argv);

    // Returns parsed tokens
    inline const std::list<token>& tokens() const noexcept { return _tokens; }

    // Returns valid options
    inline const std::unordered_set<_option>& valid_parameters() const noexcept
    {
        return _valid_parameters;
    }

    // Clear all content of CLI object
    inline void clear() noexcept
    {
        _current_option.clear();
        _current_value.clear();
        _tokens.clear();
        _valid_parameters.clear();
    }

    // Constructor is default
    CLI() noexcept = default;

    // Destructor is default
    ~CLI() noexcept = default;

private:
    // Current parameter that was read
    _option _current_option{};

    // Current parameter value that was read
    _value _current_value{};

    // Valid parameters, if it is empty, all parameters are valid
    std::unordered_set<_option> _valid_parameters{};

    // List of read tokens
    std::list<token> _tokens{};

    // Other constructors are deleted
    CLI(const CLI&) = delete;
    CLI(CLI&&) = delete;
    CLI& operator=(const CLI&) = delete;
    CLI& operator=(CLI&&) = delete;

    // Auxillary private functions
    void _extract_short_opts(const char* opt);
    void _extract_long_opt(const char* opt);
    void _append_token();
    void _throw_exception(const std::string& msg);
};

// Special type of exception
class cli_parsing_error final : public std::invalid_argument
{
public:
    explicit cli_parsing_error(const char* str) : std::invalid_argument(str) {}
    explicit cli_parsing_error(const std::string& str)
        : std::invalid_argument(str)
    {
    }
};
} // namespace CLI

#define CLI_LIB_H
#endif // CLI_LIB_H
