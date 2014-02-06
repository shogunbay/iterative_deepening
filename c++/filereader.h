#ifndef H_FILEREADER
#define H_FILEREADER

#include <fstream>
#include <string>

class FileReader
{
	std::fstream m_fs;
	class Map *m_pMap;
	bool m_Failed;

public:
	FileReader(std::string filename, class Map *pMap);
	~FileReader();

	void Read();
	bool IsValid();
};

#endif // !H_FILEREADER
