#include <string>
#include <cstdlib>
#include <cctype>

#include "node.h"
#include "filereader.h"

FileReader::FileReader(std::string filename, Map *pMap)
{
	m_fs.open(filename, std::fstream::in);
	m_pMap = pMap;

	if (m_fs.is_open())
		m_Failed = false;
	else
		m_Failed = true;
}

FileReader::~FileReader()
{
	m_fs.close();
}

void FileReader::Read()
{
	int LastNodeID = -1;
	std::string Line;

	while (std::getline(m_fs, Line))
	{
		// start node
		if (Line.substr(0, 5) == "Start")
		{
			// maybe insecure
			m_pMap->m_StartNode = atoi(Line.substr(7).c_str())-1;
			continue;
		}

		// finish node
		if (Line.substr(0, 4) == "Ziel")
		{
			// maybe insecure
			m_pMap->m_FinishNode = atoi(Line.substr(6).c_str())-1;
			continue;
		}

		// node
		if (Line[0] == 'Z' && std::isdigit(Line[1]))
		{
			// maybe insecure
			LastNodeID = atoi(Line.substr(1).c_str());

			// get node name
			int StrIndex = Line.find(": ");
			std::string Name = Line.substr(StrIndex + 2);

			m_pMap->AddNode(Name, LastNodeID);
			continue;
		}

		// neighbor
		if (Line[0] == 'K' && std::isdigit(Line[1]))
		{
			// neighbor id
			int StrIndex = Line.find(": ");
			int NeighborID = atoi(Line.substr(StrIndex + 3).c_str());

			// distance
			StrIndex = Line.find(", ");
			int Distance = atoi(Line.substr(StrIndex + 2).c_str());

			m_pMap->AddNeighbor(LastNodeID, NeighborID, Distance);
		}
	}
}

bool FileReader::IsValid()
{
	return !m_Failed;
}
