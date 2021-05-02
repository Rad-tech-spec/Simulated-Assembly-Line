#include <fstream>
#include <string>
#include "LineManager.h"

size_t LineManager::m_cnt = 1;


LineManager::LineManager(const std::string filename, std::vector<Workstation*>& station, std::vector<CustomerOrder>& tobefilled)
{
	std::ifstream file(filename);
	
	if (!file.is_open())
		throw std::string(("ERROR: DID NOT OPEN FILE: ") + filename);

	Utilities temp; 
	bool flag = true;
	size_t currentP;

	std::string Record = "";
	std::string CurrentSt = "";
	std::string NextSt = "";
	

	while (!file.eof())
	{
		currentP = 0u;
		std::getline(file, Record);
		

		CurrentSt = temp.extractToken(Record, currentP, flag);
		if (flag)
			NextSt = temp.extractToken(Record, currentP, flag);
		else
			NextSt = "";


		for (auto i = 0u; i < station.size(); ++i)
			if (station[i]->getItemName() == CurrentSt)
			{
				for (auto k = 0u; k < station.size(); ++k)
					if (station[k]->getItemName() == NextSt)
					{
						station[i]->setNextStation(*station[k]);
						break;
					}

				stations.push_back(station[i]);
			}
	}
		
	file.close();

	for (auto i = 0u; i < tobefilled.size(); ++i)
		ToBeFilled.push_back(std::move(tobefilled[i]));

	m_cntCustomerOrder = ToBeFilled.size();
	AssemblyLine = station;

	
}

auto LineManager::run(std::ostream& os) -> bool
{
	CustomerOrder temp{};

	if (!ToBeFilled.empty())
	{
		*(stations[0]) += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}


	os << "Line Manager Iteration: " << m_cnt << std::endl;

	for (auto i : AssemblyLine)
		i->runProcess(os);

	for (auto k : stations)
		k->moveOrder();

	for (auto j : AssemblyLine)
		if (j->getIfCompleted(temp))
			Complete.push_back(std::move(temp));

	m_cnt++;

	return Complete.size() == m_cntCustomerOrder;
}

auto LineManager::displayCompletedOrders(std::ostream& os) const -> void
{
	for (auto& i : Complete)
		i.display(os);

}

auto LineManager::displayStations() const -> void
{
	for (auto i : AssemblyLine)
		i->display(std::cout);
}

auto LineManager::displayStationsSorted() const -> void
{
	for (auto i : stations)
		i->display(std::cout);
}
