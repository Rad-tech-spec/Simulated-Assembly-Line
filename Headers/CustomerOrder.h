#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include "Station.h"
#include "Utilities.h"


struct Item
{
	std::string m_itemName; // Name of the system part
	unsigned int m_serialNumber = 0; 
	bool m_isFilled = false; // Status of the opart that is missing or not

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder
{
	std::string m_name; // Name of the customer
	std::string m_product; // Name of the product being assembled
	unsigned int m_cntItem; // Count of the number of items for customers order
	Item** m_1stItem = nullptr; // Dynamically allocated array of pointers
	static size_t m_widthField; // Static member that holds maximum number of field


	public:
		CustomerOrder();
		CustomerOrder(std::string&);

		CustomerOrder(CustomerOrder& cus);
		CustomerOrder& operator = (const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&& cuz) noexcept;
		CustomerOrder& operator = (CustomerOrder&& cuz) noexcept;


		bool isOrderFilled() const; // Returns true if all the items in the order have been filled.
		bool isItemFilled(const std::string& itemName) const; // return flase if there is a mssing part true if item does not exist
		void fillItem(Station& station, std::ostream& os); // fills the item in the current order
		void display(std::ostream& os) const;

		~CustomerOrder();
};

#endif // !CustomerOrder_h



