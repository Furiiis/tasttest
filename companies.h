#pragma once

enum Companies
{
	POSH, GROTTY
};

std::istream& operator>> (std::istream &in, Companies & company);

std::ostream& operator<< (std::ostream &out, const Companies & company);