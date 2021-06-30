#pragma once 
#include "time.h"
#include "companies.h"

class BusTimetable
{
public:
	void LoadFromFile(const std::string & filename);
	void Emplace(std::map<std::pair<Time, Time>, Companies>::iterator it, const Time &depart_time, 
		         const Time &arrive_time, Companies company); // delete and create new
	void Add(const Time &depart_time, const Time &arrive_time, Companies company);
	void WriteDatabaseToOutput(std::ostream & out) const;
	std::map<std::pair<Time, Time>, Companies> GetBusTimetable() const;
private:
	std::map<std::pair<Time, Time>, Companies> timedatabase;
};