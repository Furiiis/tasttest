#include "time.h"
#include <tuple>
#include <iostream>
#include <string>
#include <iomanip> 

void Time::SetTime(int _hour, int _minute)
{
	hour = _hour;
	minute = _minute;
}
std::pair<int, int> Time::GetTime() const
{
	return std::pair<int, int>(hour, minute);
}

bool operator < (const Time &lhs, const Time &rhs)
{
	return lhs.GetTime() < rhs.GetTime();
}

bool operator > (const Time &lhs, const Time &rhs)
{
	return lhs.GetTime() > rhs.GetTime();
}

bool operator == (const Time &lhs, const Time &rhs)
{
	return lhs.GetTime() == rhs.GetTime();
}

Time operator - (const Time &lhs, const Time &rhs)
{
	int min1 = lhs.GetTime().first * 60 + (lhs.GetTime().second);
	int min2 = rhs.GetTime().first * 60 + (rhs.GetTime().second);
	if (lhs < rhs)
	{
		min1 += 24 * 60;
	}
	return { (min1 - min2) / 60,  (min1 - min2) % 60 };
}


Time operator + (const Time &lhs, const Time &rhs)
{
	int min1 = lhs.GetTime().first * 60 + (lhs.GetTime().second);
	int min2 = rhs.GetTime().first * 60 + (rhs.GetTime().second);

	if (min1 + min2 > 1439) //23:59
	{
		return { (min1 + min2 - 1440) / 60,  (min1 + min2 - 1440) % 60 };
	}
	else
	{
		return { (min1 + min2) / 60,  (min1 + min2) % 60 };
	}
}

std::istream& operator>> (std::istream &in, Time &time)
{
	int hour, minute;
	in >> hour;
	in.ignore(1);
	in >> minute;
	time.SetTime(hour, minute);
	return in;
}

std::ostream& operator<< (std::ostream &out, const Time &time)
{
	out << std::setw(2);

	out << std::setfill('0');
	out << std::setw(2) << time.GetTime().first << ":" << std::setw(2) << time.GetTime().second;

	return out;
}