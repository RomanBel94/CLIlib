#pragma once
#ifndef CLI_LIB_H

#include <unordered_set>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
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
		int argc{ 0 };
		char** argv{ nullptr };

		_Param _current_param{};
		_Value _current_value{};

		std::unordered_set<_Param> _valid_parameters{};
		std::list<token> _tokens{};

		CLI(const CLI&) = delete;
		CLI(CLI&&) = delete;
		CLI& operator=(const CLI&) = delete;
		CLI& operator=(const CLI&&) = delete;

		bool _is_valid(const std::string& argument) const noexcept;

	public:

		CLI(int argc, char** argv) : argc(argc), argv(argv) {}
		~CLI() = default;

		const auto& tokens() const noexcept { return _tokens; }
		void add_option(const std::string& opt) { _valid_parameters.emplace(opt); }

		void parse_arguments();

	};

	class CLI_parsing_error : std::runtime_error
	{
	public:
		CLI_parsing_error(const char* str) : runtime_error(str) {}
		CLI_parsing_error(const std::string& str) : runtime_error(str) {}
		CLI_parsing_error(const runtime_error& error) : runtime_error(error) {}
	};
}

#define CLI_LIB_H
#endif
