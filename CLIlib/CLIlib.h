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
	class Token
	{
	private:

		std::string _key;
		std::string _value;

	public:

		Token(std::string& key, std::string& value) : _key(key), _value(value) {}
		Token(const std::string& key, const std::string& value) : _key(key), _value(value) {}
		Token(const std::pair<std::string, std::string>& pair) : _key(pair.first), _value(pair.second) {}
		Token(std::string&& key, std::string&& value) noexcept : _key(std::move(key)), _value(std::move(value)) {}
		Token& operator=(const Token& rhs);
		//Token& operator=(Token&& rhs) noexcept;
		bool operator==(const Token& rhs) const noexcept { return _key == rhs._key; }
		friend std::ostream& operator<<(std::ostream& stream, const Token& token);
		friend std::ofstream& operator<<(std::ofstream& stream, const Token& token);

		struct Hash{ size_t operator()(const Token& token) const { return std::hash<std::string>()(token.key()); }};

		const std::string& key() const noexcept { return _key; }
		const std::string& value() const noexcept { return _value; }
	};

	class CLI
	{
	private:
		int argc{ 0 };
		char** argv{ nullptr };

		std::string _current_key{};
		std::string _current_value{};

		std::unordered_set<Token, Token::Hash> _collected_data{};
		std::unordered_set<std::string> _valid_arguments{};
		std::list<Token> _tokens{};

		CLI(const CLI&) = delete;
		CLI(CLI&&) = delete;
		CLI& operator=(const CLI&) = delete;
		CLI& operator=(const CLI&&) = delete;

		bool _is_valid(const std::string& argument) const noexcept;

	public:

		CLI(int argc, char** argv) : argc(argc), argv(argv) {}
		~CLI() = default;

		const auto& collected_data() const noexcept { return _collected_data; }
		const auto& tokens() const noexcept { return _tokens; }
		void add_option(const std::string& opt) { _valid_arguments.emplace(opt); }

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
