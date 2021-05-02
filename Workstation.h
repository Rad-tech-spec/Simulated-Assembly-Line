#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"


// Object that manages a single Item on the assembly line.
class Workstation : public Station
{
	std::deque<CustomerOrder> m_orders; // CX order comes in from one side and exits from another.
	Workstation* m_pNextStation;

	public:
		Workstation();
		Workstation(const std::string& str);

		//Delete copy & move operators-------------------------
		Workstation(const Workstation&) = delete;
		Workstation& operator = (const Workstation&) = delete;
		Workstation(Workstation&&) noexcept = delete;
		Workstation& operator = (Workstation&&) noexcept = delete;

		
		void runProcess(std::ostream& os); 
		bool moveOrder();
		void setNextStation(Station& station);
		const Workstation* getNextStation() const;
		bool getIfCompleted(CustomerOrder& order);
		void display(std::ostream& os);
		Workstation& operator+=(CustomerOrder&&);
};
#endif // WORKSTATION_H