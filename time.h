#pragma once
#include <tuple>
#include <iostream>
#include <string>
#include <map>

class Time
{
private:
	int hour;
	int minute;
public:
	Time() {}
	Time(int _hour, int _minute) : hour(_hour), minute(_minute) {}
	void SetTime(int _hour, int _minute);	
	std::pair<int, int> GetTime() const;
};

bool operator < (const Time &lhs, const Time &rhs);

bool operator > (const Time &lhs, const Time &rhs);

bool operator == (const Time &lhs, const Time &rhs);

Time operator - (const Time &lhs, const Time &rhs);

Time operator + (const Time &lhs, const Time &rhs);

std::istream& operator>> (std::istream &in, Time &time);

std::ostream& operator<< (std::ostream &out, const Time &time);