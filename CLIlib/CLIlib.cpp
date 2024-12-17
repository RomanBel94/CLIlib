#include "CLIlib.h"

namespace CLI
{
	Token& Token::operator=(const Token& rhs)
	{
		this->_key = rhs._key;
		this->_value = rhs._value;
		return *this;
	}

	//Token& Token::operator=(Token&& rhs) noexcept
	//{
	//	std::swap(this->_key, rhs._key);
	//	std::swap(this->_value, rhs._value);
	//	return *this;
	//}

	std::ostream& operator<<(std::ostream& stream, const Token& token)
	{
		stream << token._key << ' ' << token._value;
		return stream;
	}

	std::ofstream& operator<<(std::ofstream& stream, const Token& token)
	{
		stream << token._key << ' ' << token._value;
		return stream;
	}

	void CLI::parse_arguments()
	{
		_current_key = "main";
		_current_value = argv[0];

		if (_is_valid(_current_key))
			_collected_data.emplace(_current_key, _current_value);
		else
			throw CLI_parsing_error("ERROR: Invalid argument");

		for (int i = 1; i < argc; ++i) {}

		for (const auto& token : _collected_data) _tokens.emplace_back(token);
	}

	bool CLI::_is_valid(const std::string& argument) const noexcept
	{
		return _valid_arguments.find(argument) != _valid_arguments.end();
	}
}
