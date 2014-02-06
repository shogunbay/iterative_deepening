#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>

#include "node.h"
#include "filereader.h"

int main(int argc, const char* argv[])
{
	// for mesuring the time
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	std::string filename = "";

	// get filename
	if (argc > 1)
		filename = argv[1];
	else // no file specified... close program
	{
		std::cout << "no file specified!";

		std::cin.clear();
		std::cin.get();
		return 0;
	}

	// create map
	Map *pMap = new Map();

	// read file
	FileReader *pReader = new FileReader(filename, pMap);
	if (pReader->IsValid())
	{
		pReader->Read();
		delete pReader;
	}
	else // file not found... close program
	{
		delete pReader;
		delete pMap;
		std::cout << "file not found!";

		std::cin.clear();
		std::cin.get();
		return 0;
	}

	// calculate way
	pMap->GetWay();

	// print result
	std::cout << pMap->Costs() << std::endl;
	pMap->PrintWay();

	// time needed
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	std::cout << "Time needed " << time_span.count() << " seconds." << std::endl;

	// delete map
	delete pMap;

	// dont close the fucking window
	std::cin.clear();
	std::cin.get();
	return 0;
}
