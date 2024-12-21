﻿#pragma once
#ifndef CLI_LIB_H

#include <unordered_set>
#include <stdexcept>
#include <cctype>
#include <memory>
#include <string>
#include <list>

#define key first
#define value second

namespace CLI
{
	class CLI
	{
    using _Param = std::string;
    using _Value = std::string;
    using token = std::pair<_Param, _Value>;

	private:

        static constexpr auto DIVIDER = '-';
        static constexpr auto EMPTY = "";

		_Param _current_param{};
		_Value _current_value{};

		std::unordered_set<_Param> _valid_parameters{ EMPTY };
		std::list<token> _tokens{};

		CLI() = default;
		CLI(const CLI&) = delete;
		CLI(CLI&&) = delete;
		CLI& operator=(const CLI&) = delete;
		CLI& operator=(CLI&&) = delete;

		void _extract_short_opts(const char* opts);
		void _extract_long_opt(const char* opt);
		void _append_token();
		void _validate_current_arg() const;
        void _check_empty_option(const char* opt);

	public:

		static std::shared_ptr<CLI>& get_instance();

		~CLI() = default;

		const auto& tokens() const noexcept { return _tokens; }

		void add_opt(const char opt);
        void add_opt(const _Param& opt);
		void add_opt(const std::initializer_list<char>& list);
		void add_opt(const std::initializer_list<_Param>& list);

        template<typename ...Args>
        void add_opt(Args&& ...args) { add_opt({args...}); }

		void add_long_opt(const _Param& opt);
        void add_long_opt(const std::initializer_list<_Param>& list);

        template<typename ...Args>
        void add_long_opt(Args&&... args) { add_long_opt({args...}); }

		void parse_args(int argc, char** argv);
		void clear();

	};

	class cli_parsing_error : public std::runtime_error
	{
	public:
		cli_parsing_error(const char* str) : runtime_error(str) {}
		cli_parsing_error(const std::string& str) : runtime_error(str) {}
		cli_parsing_error(const runtime_error& error) : runtime_error(error) {}
		cli_parsing_error(runtime_error&& error) : runtime_error(std::move(error)) {}
	};
}

#define CLI_LIB_H
#endif
