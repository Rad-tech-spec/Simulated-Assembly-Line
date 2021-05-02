#ifndef LINEMANAGER_H	
#define LINEMANAGER_H	
#include<vector>
#include"Workstation.h"


class LineManager
{
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Complete;
	std::vector<Workstation*> stations;
	static size_t m_cnt;
	size_t m_cntCustomerOrder; // The number of CustumerOrder object has assebly line started with.


	public:
		LineManager(const std::string filename, std::vector<Workstation*>& station,std::vector<CustomerOrder>& tobefilled);

		bool run(std::ostream& os);
		void displayCompletedOrders(std::ostream& os) const;
		void displayStations() const;
		void displayStationsSorted() const;
};
#endif




