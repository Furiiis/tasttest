#include "bustimetable.h"

#include <algorithm>
#include <tuple>
#include <string>
#include <map>
#include <fstream>
#include <sstream> 
#include <iomanip> 

void BusTimetable::LoadFromFile(const std::string & filename)
{
	std::ifstream file(filename);
	Companies company;
	Time arrive_time, depart_time;
	while (!file.eof())
	{
		std::string str;
		getline(file, str);
		std::istringstream is(str);		
		if (str.empty()) continue;
		is >> company;
		is.ignore(1);
		is >> depart_time;
		is.ignore(1);
		is >> arrive_time;
		Add(depart_time, arrive_time, company);
	}
}
void BusTimetable::Emplace(std::map<std::pair<Time, Time>, Companies>::iterator it, const Time &depart_time,
	const Time &arrive_time, Companies company)
{
	timedatabase.erase(it);
	timedatabase[std::pair<Time, Time>(arrive_time, depart_time)] = company;
}
void BusTimetable::Add(const Time &depart_time, const Time &arrive_time, Companies company)
{
	if (arrive_time - depart_time > Time(01, 00))
		return;

	std::map<std::pair<Time, Time>, Companies>::iterator it;
	if (depart_time > Time(23, 00))
	{
		it = timedatabase.begin();
	}
	else
	{
		it = timedatabase.lower_bound(std::pair<Time, Time>(depart_time, arrive_time));
	}

	while (it != timedatabase.end() && 
		((it->first.first < Time(23, 00) && it->first.first > Time(1, 00)) ? 
			it->first.first < depart_time + Time(1, 0) : 
			it->first.first > it->first.first - Time(0, 1) || it->first.first < depart_time + Time(1, 0))) 
	{
		if (it->first == std::pair<Time, Time>(arrive_time, depart_time)) /// == 
		{
			if (company == Companies::GROTTY)
				return;
			else if (it->second == Companies::GROTTY)
			{
				it->second = Companies::POSH;
			}
			it++;
			continue;
		}

		if (it->first.first == arrive_time) //  (]  10:00-10:34		09:44-10:34
		{
			if (it->first.first > Time(1, 0)) {
				if (it->first.second < depart_time)
				{
					Emplace(it, depart_time, arrive_time, company);					
				}
				return;
			}
			else
			{   // handle cases as 23 - 01 : (23:30-05:00)
				if ((it->first.second < Time(1, 0) && depart_time < Time(1, 0)) ||
					(it->first.second > Time(23, 0) && depart_time > Time(23, 0)))
				{
					if (it->first.second < depart_time)
					{						
						Emplace(it, depart_time, arrive_time, company);
					}
					return;
				}
				if (it->first.second < Time(1, 0) && depart_time > Time(1, 0))
				{
					return;
				}
				if (it->first.second > Time(23, 0) && depart_time < Time(1, 0))
				{					
					Emplace(it, depart_time, arrive_time, company);
					return;
				}
				
			}
		}

		if (it->first.second == depart_time)            // [) 10:00-10:34		10:00-10:55
		{
			if (it->first.second < Time(23, 00)) {
				if (it->first.first > arrive_time)
				{					
					Emplace(it, depart_time, arrive_time, company);
				}
				return;
			}
			else 
			{	// handle cases as 23 - 01 : (23:30-05:00)
				if (it->first.first > Time(23, 0) && arrive_time < Time(1, 00))
				{
					return;
				}
				if (it->first.first < Time(1, 0) && arrive_time > Time(23, 00))
				{					
					Emplace(it, depart_time, arrive_time, company);
					return;
				}
				if ((it->first.first < Time(1, 0) && arrive_time < Time(1, 00)) || 
					(it->first.first > Time(23, 0) && arrive_time > Time(23, 00)))
				{
					if (it->first.first > arrive_time)
					{						
						Emplace(it, depart_time, arrive_time, company);
					}
					else return;
				}				
			}
		}

		if (it->first.second > Time(23, 00) && it->first.first < Time(1, 0))	///()  10:00 - 10:15	 9:55 - 10:43
		{
			if (depart_time < it->first.second && depart_time > Time(23, 00) && arrive_time < Time(1, 0) && arrive_time > it->first.first)
			{
				return;
			}
			if (depart_time > it->first.second && depart_time > Time(23, 00) && arrive_time < Time(1, 0) && arrive_time < it->first.first)
			{
				it++;				
				Emplace(prev(it), depart_time, arrive_time, company);
				continue;
			}
			if (depart_time < it->first.first && depart_time < Time(1, 00) && arrive_time < Time(1, 0) && arrive_time < it->first.first)
			{
				it++;				
				Emplace(prev(it), depart_time, arrive_time, company);
				continue;
			}
			if (depart_time > it->first.second && depart_time > Time(23, 00) && arrive_time > Time(23, 0) && arrive_time > it->first.second)
			{
				it++;				
				Emplace(prev(it), depart_time, arrive_time, company);
				continue;
			}
		}
		else if (it->first.second < Time(1, 00) && it->first.first < Time(1, 0))
		{
			if (depart_time > Time(23, 00) && arrive_time < Time(1, 0) && arrive_time > it->first.first)
			{
				return;
			}
			if (depart_time > Time(23, 00) && arrive_time < Time(1, 0) && arrive_time < it->first.first)
			{
				it++;
				continue;
			}
		}
		else if (it->first.second > Time(23, 00) && it->first.first > Time(23, 00))
		{
			if (it->first.second < depart_time && depart_time > Time(23, 00) && arrive_time < Time(1, 0))
			{
				it++;
				continue;
			}
			if (it->first.second > depart_time && depart_time > Time(23, 00) && arrive_time < Time(1, 0))
			{
				return;
			}
		}


		if (it->first.second < depart_time && it->first.first > arrive_time)  
		{
			it++;			
			Emplace(prev(it), depart_time, arrive_time, company);
			continue;
		}
		if (it->first.second > depart_time && it->first.first < arrive_time)
		{
			return;
		}
		it++;		
	}
	timedatabase[std::pair<Time, Time>(arrive_time, depart_time)] = company;
}

void BusTimetable::WriteDatabaseToOutput(std::ostream & out) const
{
	std::ostringstream os;
	bool is_posh = false;
	for (const auto & x : timedatabase)
	{		
		if (x.second == POSH)
		{
			is_posh = true;
			out << x.second << " " << x.first.second << " " << x.first.first << "\n";
		}
		if (x.second == GROTTY)
			os << x.second << " " << x.first.second << " " << x.first.first << "\n";
	}
	if (is_posh)
		out << "\n" << os.str();
	else	
		out << os.str();	
}

std::map<std::pair<Time, Time>, Companies> BusTimetable::GetBusTimetable() const
{
	return timedatabase;
}