#include <string>
#include "companies.h"

std::istream& operator>> (std::istream &in, Companies & company)
{
	std::string str;
	in >> str;
	if (str == "Posh")
		company = POSH;
	if (str == "Grotty")
		company = GROTTY;
	return in;
}

std::ostream& operator<< (std::ostream &out, const Companies & company)
{
	switch (company)
	{
	case Companies::GROTTY:
		out << "Grotty";
		break;
	case Companies::POSH:
		out << "Posh";
		break;
	}
	return out;
}