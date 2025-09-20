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
    using _Param = std::string;
    using _Value = std::string;
    using token = std::pair<_Param, _Value>;

    // Parse command-line arguments and place them into std::list of tokens
    void parse_args(int argc, char** argv);

    // Returns parsed tokens
    inline const std::list<token>& tokens() const noexcept { return _tokens; }

    // Returns valid options
    inline const std::unordered_set<_Param>& valid_parameters() const noexcept
    {
        return _valid_parameters;
    }

    // Add new valid short option(s) to be parsed
    template <typename... Args>
    inline void add_opt(Args&&... args)
    {
        _add_opt({args...});
    }

    // Add new valid long option(s) to be parsed
    template <typename... Args>
    inline void add_long_opt(Args&&... args)
    {
        _add_long_opt({args...});
    }

    // Clear all content of CLI object
    inline void clear() noexcept
    {
        _current_param.clear();
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
    _Param _current_param{};

    // Current parameter value that was read
    _Value _current_value{};

    // Valid parameters, if it is empty, all parameters are valid
    std::unordered_set<_Param> _valid_parameters{};

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
    inline void _throw_exception(const std::string& msg);
    bool _is_valid_token(const _Param& opt) const noexcept;

    // Overloaded functions for adding new options to be valid
    void _add_opt(char opt);
    void _add_opt(const _Param& opts);
    void _add_opt(const std::initializer_list<char>&& opt_list);
    void _add_long_opt(const _Param& long_opt);
    void _add_long_opt(const std::initializer_list<_Param>&& opt_list);
};

// Special type of exception
class cli_parsing_error final : public std::runtime_error
{
public:
    explicit cli_parsing_error(const char* str) : std::runtime_error(str) {}
    explicit cli_parsing_error(const std::string& str) : std::runtime_error(str)
    {
    }
    explicit cli_parsing_error(const std::runtime_error& error)
        : std::runtime_error(error)
    {
    }
    explicit cli_parsing_error(std::runtime_error&& error) noexcept
        : std::runtime_error(std::move(error))
    {
    }
};
} // namespace CLI

#define CLI_LIB_H
#endif // CLI_LIB_H
