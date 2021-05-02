#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include "Utilities.h"

	class Station
	{
		std::string m_name;
		std::string m_description;
		size_t m_id;
		size_t m_serialNum;
		size_t m_numStock;

		static size_t m_widthField;
		static size_t id_generator;

		public:
			Station();
			Station(const std::string& str);

			// Copy operators----------------------
			Station(const Station& s);
			Station& operator = (const Station& s);
			Station(Station&& s) noexcept;
			Station& operator = (Station&& s) noexcept;

			// Set & Return values-----------------
			const std::string& getItemName() const;
			unsigned int getNextSerialNumber(); // Returns & Increments
			unsigned int getQuantity() const; 
			void updateQuantity(); // Subtracts one from the m_numStock;

			// Display-----------------------------
			void display(std::ostream& os, bool full) const;
	};
#endif
