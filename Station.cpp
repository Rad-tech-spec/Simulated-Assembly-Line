#include <iomanip>
#include <string>
#include "Station.h"

	size_t Station::id_generator = 0u;
	size_t Station::m_widthField = 0u;

	Station::Station()
	{
		this->m_serialNum = 0u;
		this->m_numStock = 0u;
		this->m_id = 0u;
		this->m_description = "";
		this->m_name = "";
	}


	Station::Station(const std::string& str) : Station()
	{
		Utilities temp;
		bool flag = true;
		size_t currentP = 0u;
		m_id = id_generator++;

		for (auto i = 0u; i < 4; ++i)
		{
			if (flag)
			{
				switch (i)
				{
					case 0:
						this->m_name = temp.extractToken(str, currentP, flag);
						break;
					case 1: 
						this->m_serialNum = std::stoi(temp.extractToken(str, currentP, flag));
						break;
					case 2: 
						this->m_numStock = std::stoi(temp.extractToken(str, currentP, flag));
						break;
					case 3: 
						this->m_description = temp.extractToken(str, currentP, flag);
						break;
					default:
					break;
				}

				if (i < 3)
				{
					if (temp.getFieldWidth() > m_widthField)
						m_widthField = temp.getFieldWidth();
				}
			}
		}
	}

	Station::Station(const Station& s)
	{
		this->operator=(s);
	}
	
	auto Station::operator=(const Station& s) -> Station& 
	{
		if (this != &s)
		{
			this->m_name = s.m_name;
			this->m_numStock = s.m_numStock;
			this->m_serialNum = s.m_serialNum;
			this->m_id = s.m_id;
			this->m_description = s.m_description;
			this->id_generator = s.id_generator;
			this->m_widthField = s.m_widthField;
		}

		return *this;
	}

	Station::Station(Station&& s) noexcept
	{
		this->operator=(s);
	}

	auto Station::operator=(Station&& s) noexcept -> Station&
	{
		if (this != &s)
		{
			this->m_name = s.m_name;
			this->m_numStock = s.m_numStock;
			this->m_serialNum = s.m_serialNum;
			this->m_id = s.m_id;
			this->m_description = s.m_description;
			this->id_generator = s.id_generator;
			this->m_widthField = s.m_widthField;

			s.m_name = "";
			s.m_numStock = 0u;
			s.m_serialNum = 0u;
			s.m_id = 0u;
			s.m_description = "";
			s.id_generator = 0u;
			s.m_widthField = 0u;
		}

		return *this;
	}


	auto Station::getItemName() const -> const std::string&
	{
		return this->m_name;
	}


	auto Station::getNextSerialNumber() -> unsigned int
	{
		return this->m_serialNum++;
	}


	auto Station::getQuantity() const -> unsigned int
	{
		return this->m_numStock;
	}


	auto Station::updateQuantity() -> void
	{
		if (this->m_numStock != 0)
			--this->m_numStock;
	}


	auto Station::display(std::ostream& os, bool full) const -> void
	{
		
		os << "[" << std::setw(3) << std::setfill('0') << std::right << this->m_id+1 << "] "; 
		os << "Item: " << std::setfill(' ') << std::setw(m_widthField) << std::left << getItemName();
		os << " [" << std::setw(6) << std::setfill('0') << std::right << m_serialNum << "]" << std::setfill(' ');

		if (full)
			os << " Quantity: " << std::setw(m_widthField) << std::left << this->m_numStock << " Description: "
			<< this->m_description << std::endl;
		else
			os << std::endl;
	}
