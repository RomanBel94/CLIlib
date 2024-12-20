#pragma once
#ifndef CLI_LIB_H

#include <unordered_set>
#include <stdexcept>
#include <cctype>
#include <memory>
#include <string>
#include <list>


namespace CLI
{
	class CLI
	{
    using _Param = std::string;
    using _Value = std::string;
    using token = std::pair<_Param, _Value>;

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

		void _extract_keys(const char* keys);
		void _append_token();
		void _validate_current_arg() const;

	public:

		static std::shared_ptr<CLI>& get_instance() noexcept;
		~CLI() = default;

		const auto& tokens() const noexcept { return _tokens; }

		void add_option(const _Param& opt) { _valid_parameters.emplace(opt); }
		void add_options(const std::initializer_list<_Param>& list);
		void add_options(const _Param& params);
		void parse_arguments(int argc, char** argv);

	};

	class cli_parsing_error : public std::runtime_error
	{
	public:
		cli_parsing_error(const char* str) : runtime_error(str) {}
		cli_parsing_error(const std::string& str) : runtime_error(str) {}
		cli_parsing_error(const std::string&& str) : runtime_error(std::move(str)) {}
		cli_parsing_error(const runtime_error& error) : runtime_error(error) {}
	};
}

#define CLI_LIB_H
#endif
