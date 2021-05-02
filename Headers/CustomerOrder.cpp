#include "CustomerOrder.h"
#include <vector>
#include <iomanip>
size_t CustomerOrder::m_widthField;


CustomerOrder::CustomerOrder()
{
	this->m_name = "";
	this->m_product = "";
	this->m_cntItem = 0u;
	this->m_1stItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string& str) : CustomerOrder()
{
	Utilities temp;
	bool flag = true;
	size_t currentP = 0u;
	size_t m_count = 1u;
	char delimi = temp.getDeilimiter();
	
	for (auto i = 0u; i < str.size(); ++i)
	{
		if (str[i] == delimi)
			++m_count;
	}
	
	std::vector<std::string> temperory;

	for (auto i = 0u; i < m_count; ++i)
	{
		if (flag)
		{
			switch (i)
			{
				case 0:	
					this->m_name = temp.extractToken(str, currentP, flag);
					break;
				case 1:
					this->m_product = temp.extractToken(str, currentP, flag);
					break;
				default:
					temperory.push_back(temp.extractToken(str, currentP, flag));
					break;
			}

			if(i < m_count - 1)
				if (temp.getFieldWidth() > m_widthField)
					m_widthField = temp.getFieldWidth();
		}
	}


	m_cntItem = temperory.size();
	m_1stItem = new Item * [m_cntItem];
	
	for (auto i = 0u; i < m_cntItem; ++i)
		m_1stItem[i] = new Item(temperory[i]);
}

CustomerOrder::CustomerOrder(CustomerOrder& cus)
{
	throw "----> ERROR: Cannot make copies.";
}

CustomerOrder::CustomerOrder(CustomerOrder&& cus) noexcept
{
	this->operator=(std::move(cus));
}

auto  CustomerOrder::operator=(CustomerOrder&& cus) noexcept -> CustomerOrder&
{
	if (this != &cus)
	{
		if (m_1stItem)
		{
			for (auto i = 0u; i < m_cntItem; ++i)
				delete m_1stItem[i];

			delete[] m_1stItem;
			m_1stItem = nullptr;
		}
		
		this->m_name = cus.m_name;
		this->m_product = cus.m_product;
		this->m_widthField = cus.m_widthField;
		this->m_cntItem = cus.m_cntItem;
		this->m_1stItem = cus.m_1stItem;

		cus.m_name = "";
		cus.m_product = "";
		cus.m_cntItem = 0u;
		cus.m_1stItem = nullptr;
	}

	return *this;
}

auto CustomerOrder::isOrderFilled() const -> bool
{
	size_t s = 0u;
	for (auto i = 0u; i < m_cntItem; ++i)
		if (m_1stItem[i]->m_isFilled)
			s++;

	if (s < m_cntItem)
		return false;
	else
		return true;
}

auto CustomerOrder::isItemFilled(const std::string& itemName) const -> bool
{
	for (auto i = 0u; i < m_cntItem; ++i)
		if (m_1stItem[i]->m_itemName == itemName)
		{
			return m_1stItem[i]->m_isFilled;
		}
	return true;
}

auto CustomerOrder::fillItem(Station& station, std::ostream& os) -> void
{
	for (auto i = 0u; i < m_cntItem; ++i)
	{
		if (station.getItemName() == m_1stItem[i]->m_itemName && station.getQuantity() > 0)
		{
			station.getQuantity();

			m_1stItem[i]->m_serialNumber = station.getNextSerialNumber();
			m_1stItem[i]->m_isFilled = true;

			station.updateQuantity();
			os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;

		}
		if (station.getItemName() == m_1stItem[i]->m_itemName && station.getQuantity() <= 0)
			os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
	}
		
}

auto CustomerOrder::display(std::ostream& os) const -> void
{
	std::string stat = "";
	os << m_name << " - " << m_product << std::endl;

	for (auto i = 0u; i < m_cntItem; ++i)
	{
		if ((m_1stItem[i]->m_isFilled))
			stat = "FILLED";
		else
			stat = "MISSING";

		os << "[" << std::right << std::setfill('0') << std::setw(6) << m_1stItem[i]->m_serialNumber << "] ";
		os << std::left << std::setfill(' ') << std::setw(m_widthField) << m_1stItem[i]->m_itemName << " - " << stat << std::endl;
	}
}

CustomerOrder::~CustomerOrder()
{
	for (auto i = 0u; i < m_cntItem; ++i)
		delete this->m_1stItem[i];

	delete[] this->m_1stItem;
}
