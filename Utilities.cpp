#include "Utilities.h"

	char Utilities::m_delimiter = '|';

	Utilities::Utilities()
	{
		this->m_widthField = 1;
	}

	auto Utilities::extractToken(const std::string str, size_t& next_pos, bool& more) -> std::string
	{
		std::string token = "";
		size_t current = 0u;

		current = str.find(m_delimiter, next_pos);
		token = str.substr(next_pos, current - next_pos);

		if (current == std::string::npos)
		{
			if (token[token.length() - 1] == '\r')
				token = token.substr(0, token.length() - 1);

			more = false;
			//throw std::string("Invalid data!");
		
		}
		else 
		{
			more = true; // Set more as a parameter to true;
			next_pos = ++current;
			if (this->getFieldWidth() < token.length()) // Update size;
			{
				this->setFieldWidth(token.length());
			}
		}

		return token; // Return extracted token;
	}

	auto Utilities::setFieldWidth(size_t newWidth) -> void
	{
		if (newWidth)
		{
			this->m_widthField = newWidth;
		}
	}

	auto Utilities::getFieldWidth() const -> size_t
	{
		return this->m_widthField;
	}

	auto Utilities::setDelimiter(const char newDelimiter) -> void
	{
		m_delimiter = newDelimiter; // Static members
	}

	auto Utilities::getDeilimiter() -> char
	{
		return m_delimiter;
	}
