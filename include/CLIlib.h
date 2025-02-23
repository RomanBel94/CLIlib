#pragma once
#ifndef CLI_LIB_H

#include <cctype>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace CLI
{
class CLI
{
public:
    using _Param = std::string;
    using _Value = std::string;
    using token = std::pair<_Param, _Value>;

    static const std::shared_ptr<CLI>& get_instance();
    void parse_args(int argc, char** argv);

    inline const std::list<token>& tokens() const noexcept { return _tokens; }

    template <typename... Args>
    void add_opt(Args&&... args)
    {
        _add_opt({args...});
    }

    template <typename... Args>
    void add_long_opt(Args&&... args)
    {
        _add_long_opt({args...});
    }

    void clear();

    ~CLI() = default;

private:
    _Param _current_param{};
    _Value _current_value{};

    std::unordered_set<_Param> _valid_parameters{};
    std::list<token> _tokens{};

    CLI() = default;
    CLI(const CLI&) = delete;
    CLI(CLI&&) = delete;
    CLI& operator=(const CLI&) = delete;
    CLI& operator=(CLI&&) = delete;

    void _extract_short_opt(const char* opt);
    void _extract_long_opt(const char* opt);
    void _append_token();
    void _validate_current_arg();
    void _check_empty_option(const char* opt);
    inline bool _is_valid_token(const _Param& opt) const noexcept;

    void _add_opt(char opt);
    void _add_opt(const _Param&& opts);
    void _add_opt(const std::initializer_list<char>&& opt_list);
    void _add_long_opt(const std::initializer_list<_Param>&& opt_list);
};

class cli_parsing_error : public std::runtime_error
{
public:
    explicit cli_parsing_error(const char* str) : runtime_error(str) {}
    explicit cli_parsing_error(const std::string& str) : runtime_error(str) {}
    explicit cli_parsing_error(const runtime_error& error)
        : runtime_error(error)
    {
    }
    explicit cli_parsing_error(runtime_error&& error)
        : runtime_error(std::move(error))
    {
    }
};
} // namespace CLI

#define CLI_LIB_H
#endif // CLI_LIB_H
