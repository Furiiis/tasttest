#include <utility>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream> 
#include <iomanip> 
#include <assert.h> 
#include "time.h"
#include "companies.h"
#include "bustimetable.h"


void AllTests();

int main()
{
	AllTests();
	{
		BusTimetable td;
		td.LoadFromFile("input_test2.txt");
		
		std::ofstream out;          
		out.open("default.txt"); 
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}		
	}	
	system("pause");
	return 0;
}