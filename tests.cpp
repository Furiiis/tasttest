#include <iostream>
#include <fstream>
#include <sstream> 
#include <assert.h> 
#include "bustimetable.h"

void DefaultTests();
void StrongTests();

void AllTests()
{
	DefaultTests();
	StrongTests();
}

void DefaultTests()
{
	{
		//DEFAULT TEST FROM TASK
		BusTimetable td;
		td.LoadFromFile("input_test1.txt");
		std::ofstream out;
		out.open("default.txt");
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}
		out.close();
		BusTimetable def_td;
		def_td.LoadFromFile("out_test1.txt");
		assert(td.GetBusTimetable() == def_td.GetBusTimetable());
		std::cout << "1 test - OK" << std::endl;
	}
	{
		//DEFAULT MY TEST FROM TASK (RANDOM STRINGS)
		BusTimetable td;
		td.LoadFromFile("input_test2.txt");
		std::ofstream out;
		out.open("default.txt");
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}
		out.close();
		BusTimetable def_td;
		def_td.LoadFromFile("out_test2.txt");
		assert(td.GetBusTimetable() == def_td.GetBusTimetable());
		std::cout << "2 test - OK" << std::endl;
	}
	{
		//DEFAULT MY TEST FROM TASK (RANDOM STRINGS, WITHOUT 23:30 - 00:30 cases)
		BusTimetable td;
		td.LoadFromFile("input_test3.txt");
		std::ofstream out;
		out.open("default.txt");
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}
		out.close();
		BusTimetable def_td;
		def_td.LoadFromFile("out_test3.txt");
		assert(td.GetBusTimetable() == def_td.GetBusTimetable());
		std::cout << "3 test - OK" << std::endl;
	}
}

void StrongTests()
{
	{
		//23:30 - 00:30 cases)
		//  Grotty 00:00 00 : 01
		//	Posh 23 : 59 00 : 01
		//	Grotty 00 : 00 00 : 02
		//	Grotty 23 : 59 00 : 02
		BusTimetable td;
		td.LoadFromFile("input_test4.txt");
		std::ofstream out;
		out.open("default.txt");
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}
		out.close();
		BusTimetable def_td;
		def_td.LoadFromFile("out_test4.txt");
		assert(td.GetBusTimetable() == def_td.GetBusTimetable());
		std::cout << "4 test - OK" << std::endl;
	}
	{
		//23:30 - 00:30 cases)
		//  Grotty 23:30 23:50
		//  Posh 00:01 00 : 08
		//	Grotty 23:20 00 : 01
		//	Grotty 23 : 35 23 : 45
		BusTimetable td;
		td.LoadFromFile("input_test5.txt");
		std::ofstream out;
		out.open("default.txt");
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}
		out.close();
		BusTimetable def_td;
		def_td.LoadFromFile("out_test5.txt");
		assert(td.GetBusTimetable() == def_td.GetBusTimetable());
		std::cout << "5 test - OK" << std::endl;
	}
	{
		//23:30 - 00:30 cases)
		BusTimetable td;
		td.LoadFromFile("input_test6.txt");
		std::ofstream out;
		out.open("default.txt");
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}
		out.close();
		BusTimetable def_td;
		def_td.LoadFromFile("out_test6.txt");
		assert(td.GetBusTimetable() == def_td.GetBusTimetable());
		std::cout << "6 test - OK" << std::endl;
	}
	{
		//23:30 - 00:30 cases)
		BusTimetable td;
		td.LoadFromFile("input_test7.txt");
		std::ofstream out;
		out.open("default.txt");
		if (out.is_open())
		{
			td.WriteDatabaseToOutput(out);
		}
		out.close();
		BusTimetable def_td;
		def_td.LoadFromFile("out_test7.txt");
		assert(td.GetBusTimetable() == def_td.GetBusTimetable());
		std::cout << "7 test - OK" << std::endl;
	}
}