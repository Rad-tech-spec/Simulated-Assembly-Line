#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>

	class Utilities
	{
		size_t m_widthField;
		static char m_delimiter; 

		public:
			Utilities(); // Default constructor;

			std::string extractToken(const std::string str, size_t& next_pos, bool& more); // Extract token from str one by one;

			//Set & Return----------------------------------
			void setFieldWidth(size_t newWidth);
			size_t getFieldWidth() const;
			static void setDelimiter(char newDelimiter); // Static
			static char getDeilimiter(); // Static
	};

#endif // !SDDS_UTILITIES_H


